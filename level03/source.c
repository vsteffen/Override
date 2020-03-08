// gcc -fno-stack-protector -z execstack 
#include <time.h>
#include <stdio.h>

int main(int ac, char **av) {
        int buffer;

        srand(time(NULL));
        puts("***********************************");
        puts("*		level03		**");
        puts("***********************************");
        printf("Password:");
        scanf("%d", &buffer);
//        test(buffer, 0x1337d00d);
        return (0);
}