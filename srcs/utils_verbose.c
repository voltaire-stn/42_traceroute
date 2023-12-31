#include "traceroute_functions.h"

void    verbose_h_dump(t_data *dt, char *title, void *h, int len)
{
    unsigned char *bytes = (unsigned char *)h;

    if (dt->verbose && !g_end)
    {
        printf("%-10s", title);
        for (int i = 0; i < len; i = i + 2)
            printf(" %02X%02X", bytes[i], bytes[i + 1]);    
        printf("\n");
    }
}

void    verbose_full_reply(t_data *dt, void *packet)
{
    if (dt->verbose && !g_end)
        printf("\n- - - - - - - - - - - - -\n");
    verbose_h_dump(dt, "   IPH",   packet,                                                  IP_H_LEN);
    verbose_h_dump(dt, "   ICMPH", packet + IP_H_LEN,                                       ICMP_H_LEN);
    verbose_h_dump(dt, "   IPH",   packet + IP_H_LEN + ICMP_H_LEN,                          IP_H_LEN);
    verbose_h_dump(dt, "   UDPH",  packet + IP_H_LEN + ICMP_H_LEN + IP_H_LEN,               UDP_H_LEN);
    verbose_h_dump(dt, "   UDPD",  packet + IP_H_LEN + ICMP_H_LEN + IP_H_LEN + UDP_H_LEN,   UDP_D_LEN);
    if (dt->verbose && !g_end)
        printf("\n");
}

void    verbose_full_send(t_data *dt, void *packet)
{
    if (dt->verbose && !g_end)
        printf("\n- - - - - - - - - - - - -\n");
    // verbose_h_dump(dt, "   IPH",   packet,                          IP_H_LEN);
    verbose_h_dump(dt, "   UDPH",  packet + IP_H_LEN,               UDP_H_LEN);
    verbose_h_dump(dt, "   UDPD",  packet + IP_H_LEN + UDP_H_LEN,   UDP_D_LEN);
}
