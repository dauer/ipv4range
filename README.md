# ipv4range #

A simple commandline tool for calculating IP v4 ranges.

This project is very early in development, expect errors etc.

## Build / install ##

Run the Makefile in the src folder to build the binary.

    git clone git@github.com:dauer/ipv4range.git
    cd ipv4range/src/
    make
    ./ipv4range -h

## Examples ##

Getting help:

    $ ./ipv4range -h
    ipv4range 0.1 Beta
    Usage: ipv4range [OPTION]... RANGE
    Try 'ipv4range -h for more information.'
    Example: ipv4range -n 127.0.0.0-127.0.0.255

    -h    show help message
    -a    print all IP adresses in range
    -c    print IP class (A, B, C, D, E)
    -n    print IP range in CIDR format

Calculate CIDR for an IP range:

    $ ./ipv4range -n 69.208.0.0-69.208.0.255
    CIDR:    69.208.0.0/24

Listing all IPs in a range:

    $ ./ipv4range -a 69.208.0.0-69.208.0.255
    69.208.0.0
    69.208.0.1
    69.208.0.2
    69.208.0.3
    69.208.0.4
    69.208.0.5
        ...
    69.208.0.250
    69.208.0.251
    69.208.0.252
    69.208.0.253
    69.208.0.254
    69.208.0.255
