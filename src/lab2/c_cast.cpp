#include <stdio.h>

int main() {
    /* My machine use LITTLE ENDIAN */
    long long a = 0x0000'0000'414c'4f48; /* HOLA */
    char *str = (char *)&a;

    printf("%s\n", str);
}
