#include <stdlib.h>
#include <stdio.h>

/*1KB = 1024 bits (2^10); 4KB = 4 * 1024 = 4096 bits*/
#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You have to enter an address.\n");
        return -1;
    }

    unsigned int address;
    unsigned int pageNumber;
    unsigned int offset;

    address = atoi(argv[1]);
    pageNumber = address / PAGE_SIZE;
    offset = address % PAGE_SIZE;

    printf("The address %u contains:\npage number=4 offset=%u\n", address, pageNumber, offset);

    return 0;
}