#ifndef TRACEROUTE_FUNCTIONS_H
# define TRACEROUTE_FUNCTIONS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <arpa/inet.h>         // inet_ntoa
# include <netdb.h>             // addrinfo
# include <netinet/ip_icmp.h>   // struct icmphdr
# include <netinet/udp.h>       // struct udphdr
# include <libft.h>
# include <utils_colors.h>
# include <utils_constants.h>
# include <utils_options.h>
# include <traceroute_data.h>

//  craft.c
void            craft_packet(t_data *dt, char *udp_packet);

//  reach_hop.c
void            reach_hop(t_data *dt);

//  receive_reply.c
void            receive_reply(t_data *dt);

//  socket.c
void            resolve_hostname(t_data *dt);
void            resolve_address(t_data *dt);
void            bind_socket_to_src_port(t_data *dt, int src_port);
void            open_main_socket(t_data *dt);

//  options.c
void            init_options_params(t_data *dt);

//  init_data.c
void            init_probe(t_data *dt);
void            init_data(t_data *dt, t_parsed_cmd *parsed_cmd);

//  display.c
void            display_traceroute_init(t_data *dt);
void            display_hop(t_data *dt);
void            display_hop_timeout(t_data *dt);

// utils_getters.c
t_probe         *get_probe(t_lst *hop_probes, int nb);
int             get_send_port(void *packet);
int             get_reply_port(void *packet);
int             get_curr_send_port(t_data *dt);

// utils_verbose.c
void            verbose_full_reply(t_data *dt, void *packet);
void            verbose_full_send(t_data *dt, void *packet);

//  utils_debug.c
void            debug_addrinfo(struct addrinfo *ai);
void            debug_sockaddr_in(struct sockaddr_in *addr);
void            debug_one_probe(void *content);
void            debug_probes(t_data *dt);
#endif
