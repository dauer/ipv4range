typedef struct ip_addr {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
} ip_addr;

int cidr(uint32_t from, uint32_t to);

char class(uint32_t ip);

ip_addr to_ip_addr(uint32_t ip);
