#include "traceroute_functions.h"

void resolve_address(t_data *dt) // check that dest exists and resolve address if input == hostname
{
    int                 r;
    struct addrinfo     *resolved_add;
    struct addrinfo     *tmp;

    r = getaddrinfo(dt->input_dest, NULL, NULL, &resolved_add);
    // debug_addrinfo(resolved_add);
    if (r != 0)
        exit_error("traceroute: unknown host\n");
    tmp = resolved_add;
    while (tmp != NULL)
    {
        char ip_str[MAX_IP_LEN];

        ft_bzero(ip_str, MAX_IP_LEN);
        if (inet_ntop(tmp->ai_family, &((struct sockaddr_in *)tmp->ai_addr)->sin_addr, ip_str, sizeof(ip_str)) == NULL)
            exit_error("traceroute: address error: Conversion from network to presentation format failed.\n");
        dt->resolved_address = ft_strdup(ip_str);
        if (dt->resolved_address == NULL)
            exit_error("traceroute: malloc failure.\n");
        tmp = tmp->ai_next;
        break; // useful if many
    }
    // if (DEBUG)
    //     printf(C_B_RED"dt->resolved_address %s"C_RES"\n", dt->resolved_address);
    freeaddrinfo(resolved_add);
}

void resolve_hostname(t_data *dt) // useful only when input_dest is ip address (vs. hostname)
{
    char    host[MAX_HOSTNAME_LEN];
    int r = 0;

    ft_bzero(host, MAX_HOSTNAME_LEN);
    if (inet_pton(AF_INET, dt->resolved_address, &(dt->target_address.sin_addr)) <= 0)
        exit_error("traceroute: address error: Invalid IPv4 address.\n");
    r = getnameinfo((struct sockaddr*)&(dt->target_address), sizeof(dt->target_address), host, sizeof(host), NULL, 0, 0);
    if (r != 0)
        exit_error("traceroute: address error: The hostname could not be resolved. %d\n", r);
    else
    {
        dt->resolved_hostname = ft_strdup(host);
        if (dt->resolved_hostname == NULL)
            exit_error("traceroute: malloc failure.\n");
    }
    // if (DEBUG)
    //     printf(C_B_RED"dt->resolved_hostname %s"C_RES"\n", dt->resolved_hostname);
}

void    bind_socket_to_src_port(t_data *dt, int src_port)
{
    int r = 0;

    dt->local_address.sin_family = AF_INET;
    dt->local_address.sin_addr.s_addr = INADDR_ANY;
    dt->local_address.sin_port = htons(src_port);

    r = bind(dt->socket, (struct sockaddr *)&dt->local_address, sizeof(dt->local_address));
    if (r == -1)
        exit_error_clear(dt, "Error binding socket %s\n", strerror(errno));
}

void    open_main_socket(t_data *dt)
{
    int         one  = 1;

    dt->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); // change to 0 ?
    if (dt->socket < 0)
        exit_error("traceroute: socket error: Check that you have the correct rights.\n");
    if (setsockopt(dt->socket, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) < 0)
        exit_error_clear(dt, "Error setting socket options %s\n", strerror(errno));
    FD_SET(dt->socket, &dt->read_set);
    bind_socket_to_src_port(dt, dt->src_port);
}


// void set_socket_option_ttl(int socket, t_data *dt)
// {
//     int r           = 0;

//     r = setsockopt(socket, IPPROTO_IP, IP_TTL, &dt->curr_ttl, sizeof(dt->curr_ttl));
//     if (r != 0)
//         exit_error_clear(dt, "traceroute: socket error in setting TTL option: Exiting program.\n");
// }

// void set_socket_option_timeout(int socket, t_data *dt)
// {
//     int r           = 0;
//     struct timeval tv_out;
// 	tv_out.tv_sec = dt->reply_timeout;
// 	tv_out.tv_usec = 0;
//     r = setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)); // setting timeout option
//     if (r != 0)
//         exit_error_clear(dt, "traceroute: socket error in setting timeout option: Exiting program.\n");
// }
