#include <stdio.h>
#include <stdlib.h>

void __attribute__((noreturn)) Die(void) {
    printf("Dying in a custom function\n");
    exit(1);
}

int main() {
    int *nullptr = (void *)0x0;
    *nullptr = 1;

    return 0;
}
