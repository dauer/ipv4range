#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "interface.h"
#include "iprange.h"

#define OPTION_HELP  0x01
#define OPTION_CIDR  0x02
#define OPTION_CLASS 0x04
#define OPTION_ALL   0x08

int main(int argc, char* argv[]) {
    int opt;
    char* range         = NULL;
    uint32_t ip_from    = 0;
    uint32_t ip_to      = 0;
    unsigned char args  = 0;

    if(argc <= 1) {
        usage();
    } else {
        while((opt = getopt(argc, argv, "hcna")) != -1) {
            switch(opt) {
                case 'n': // NETMASK
                    args |= OPTION_CIDR;
                break;
                case 'c': // CLASS
                    args |= OPTION_CLASS;
                break;
                case 'h': // HELP
                    args |= OPTION_HELP;
                break;
                case 'a': // ALL
                    args |= OPTION_ALL;
                break;
                case '?':
                    printf("Unknown option -%c\n", optopt);
                    usage();
                break;
            }
        }
        for(; optind < argc; optind++) {
            /**
             * We expect one 'unnamed' parameter containing the ip range
             */
            range = argv[optind];
            if(parse_range(range, &ip_from, &ip_to)) {
                if(ip_from > ip_to) {
                    // Swap numbers if 'to' is smaller than 'from',
                    // we want them in increasing order...
                    ip_from = ip_from ^ ip_to;
                    ip_to   = ip_from ^ ip_to;
                    ip_from = ip_from ^ ip_to;
                }
            } else {
                exit(EXIT_FAILURE);
            }

            break;
        }

        if(args & OPTION_HELP) {
            // If help flag is set only show help message
            help();
        } else {
            if(args & OPTION_CIDR) {
                char* str = malloc(16);
                format_ip(ip_from, str);
                printf("CIDR:\t%s/%u\n", str, cidr(ip_from, ip_to));
                free(str);
            }
            if(args & OPTION_CLASS) {
                printf("Class:\t%c\n", class(ip_from));
            }
            if(args & OPTION_ALL) {
                print_range(ip_from, ip_to);
            }
        }
    }

    exit(EXIT_SUCCESS);
}
