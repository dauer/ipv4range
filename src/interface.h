#include <stdbool.h>

void usage();

void help();

bool parse_range(const char *range, uint32_t *ip1, uint32_t *ip2);

void print_range(uint32_t ip_from, uint32_t ip_to);

void format_ip(uint32_t ip, char *str);
