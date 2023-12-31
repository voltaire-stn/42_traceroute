#ifndef TRACEROUTE_DATA_H
# define TRACEROUTE_DATA_H

# include "utils_constants.h"

extern int g_end;
extern int g_sigint;

typedef struct  s_probe
{
    int                 nb;
    int                 time;
    int                 send_port;
    struct sockaddr_in  address;
    char                *name;
}               t_probe;

typedef struct  s_data
{
    // general
    char                *input_dest;
    t_lst               *act_options;
    char                *resolved_address;
    char                *resolved_hostname;
    int                 socket;
    fd_set              read_set;
    struct sockaddr_in  local_address;
    struct sockaddr_in  target_address;
    int                 dst_port;
    int                 src_port;
    // options
    int                 max_ttl;
    int                 nb_probes;
    int                 reply_timeout;
    int                 probes_interval_us;
    int                 verbose;
    // each hop
    int                 curr_ttl;
    int                 curr_probe;
    t_lst               *hop_probes;
    // time
    struct timeval      tz;
    struct timeval      init_tv;
    struct timeval      send_tv;
    struct timeval      recv_tv;
}					t_data;

// struct icmphdr
// {
//     unsigned char type;                /* message type */
//     unsigned char code;                /* type sub-code */
//     unsigned short int checksum;
//     union
//     {
//         struct
//         {
//             unsigned short int        id;
//             unsigned short int        sequence;
//         } echo;                        /* echo datagram */
//         unsigned int        gateway;        /* gateway address */
//         struct
//         {
//             unsigned short int        __unused;
//             unsigned short int        mtu;
//         } frag;                        /* path mtu discovery */
//     } un;
// };

// struct udphdr
// {
//   u_int16_t uh_sport;              /* source port */
//   u_int16_t uh_dport;              /* destination port */
//   u_int16_t uh_ulen;               /* udp length */
//   u_int16_t uh_sum;                /* udp checksum */
// };

#endif