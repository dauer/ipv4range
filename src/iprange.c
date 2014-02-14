#include <stdint.h>
#include <stdbool.h>

#include "iprange.h"

/**
 * Count how many starting digits are exactly alike.
 * This is the CIDR suffix.
 */
int cidr(uint32_t from, uint32_t to) {
    int i = 0;
    int j = 0;
    for(i = 31; i>= 0; i--) {
        /* Get i-th bit of from and to and compare them */
        if( ((from & ( 1 << i )) >> i) != ((to & ( 1 << i )) >> i) ) {
            return j;
        }
        j++;
    }
    return 0;
}

static bool is_bit_set(uint32_t ch, int i ) {
    return (1 << i) & ch;
}

char class(uint32_t ip) {
    int i;
    char c[5] = {'A','B','C','D', 'E'};
    for(i = 0; i < 5; i++) {
        if(is_bit_set(ip, 31-i) == false) {
            break;
        }
    }
    return c[i];
}

ip_addr to_ip_addr(uint32_t ip) {
    ip_addr addr;

    addr.d = 0xff & ip;
    ip >>= 8;
    addr.c = 0xff & ip;
    ip >>= 8;
    addr.b = 0xff & ip;
    ip >>= 8;
    addr.a = 0xff & ip;

    return addr;
}
