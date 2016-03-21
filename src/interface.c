#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include <stdlib.h>

#include "iprange.h"

void usage() {
    printf("ipv4range 0.1 Beta\n");
    printf("Usage: ipv4range [OPTION]... RANGE\n");
    printf("Try 'ipv4range -h for more information.'\n");
}

void help() {
    usage();
    printf("Example: ipv4range -n 127.0.0.0-127.0.0.255\n");
    printf("\n");
    printf("  -h\tshow help message\n");
    printf("  -a\tprint all IP adresses in range\n");
    printf("  -c\tprint IP class (A, B, C, D, E)\n");
    printf("  -n\tprint IP range in CIDR format\n");
}

static bool split_range(const char *r, char **ip_from, char **ip_to) {
    char *range = malloc((strlen(r) + 1) * sizeof(char));
    char *r_ptr = range;
    bool status = false;
    strcpy(r_ptr, r);
    r_ptr = strtok(range, "-");
    if(r_ptr != NULL) {
        strcpy(*ip_from, r_ptr);
        r_ptr = strtok(NULL, "-");
        if(r_ptr != NULL) {
            strcpy(*ip_to, r_ptr);
            status = true;
        }
    }
    free(range);
    return status;
}

static bool validate_addr(const char *addr) {
    regex_t myregex;
    bool valid = false;
    regcomp( &myregex,"^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$", REG_EXTENDED | REG_NOSUB );
    if (!regexec(&myregex, addr, (size_t)0 , NULL , 0 ) ) {
        valid = true;
    }
    regfree(&myregex);
    return valid;
}

static uint32_t addr_to_bin(const char *addr) {
    uint32_t from = 0;
    char *buffer = malloc((strlen(addr) + 1) * sizeof(char));
    char *tmp = NULL;
    uint32_t t = 0;
    strcpy(buffer, addr);
    /**
     * strtok() changes the first parameter, we don't want that side effect
     * with our addr parameter
     */
    tmp = buffer;
    tmp = strtok(tmp, ".");
    while(tmp != NULL) {
        t = (uint32_t)atoi(tmp);
        from <<= 8;
        from |= t;
        tmp = strtok(NULL, ".");
    }
    free(buffer);
    return from;
}

/**
 * parses a string IP range to two int IP adresses
 */
bool parse_range(const char *range, uint32_t *ip1, uint32_t *ip2) {
    regex_t myregex;
    bool status = false;
    regcomp(&myregex, "^([0-9\\.]){7,15}-([0-9\\.]){7,15}$", REG_EXTENDED | REG_NOSUB);
    if (!regexec(&myregex, range, (size_t)0 , NULL , 0 ) ) {
        char *a = malloc((strlen(range) + 1) * sizeof(char));
        char *b = malloc((strlen(range) + 1) * sizeof(char));
        split_range(range, &a, &b);
        if(validate_addr(a) && validate_addr(b)) {
            *ip1 = addr_to_bin(a);
            *ip2 = addr_to_bin(b);
            status = true;
        }
        free(a);
        free(b);
    } else {
        *ip1 = 0;
        *ip2 = 0;
    }
    regfree(&myregex);
    return status;
}

void format_ip(uint32_t ip, char *str) {
    ip_addr addr;
    addr = to_ip_addr(ip);
    sprintf(str, "%d.%d.%d.%d", addr.a, addr.b, addr.c, addr.d);
}

void print_range(uint32_t ip_from, uint32_t ip_to) {
    ip_addr addr;
    uint32_t ip = ip_from;
    while(ip <= ip_to) {
        addr = to_ip_addr(ip);
        printf("%d.%d.%d.%d\n", addr.a, addr.b, addr.c, addr.d);
        ip++;
    }
}
