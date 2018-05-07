#include <stdio.h>
#include <string.h>

int hex_to_byte(char *hex_p, char *byte_p, int size)
{
    char *hex_e = hex_p + size;
    for(; hex_p < hex_e; hex_p += 2, byte_p += 1)
    {
        sscanf(hex_p, "%2x", byte_p);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /*printf("%d\n", argc);*/
    /*printf("%d", strlen(argv[1]));*/
    printf("%02x\n", 0xab);
}
