// gcc -fno-stack-protector -z execstack 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
        char    buffer1[0x64];
        char    buffer2[0x29];
        char    buffer3[0x64];
        FILE    *file;
        int     read;

        memset(buffer1, 0, 0x64);
        memset(buffer2, 0, 0x29);
        memset(buffer3, 0, 0x64);
        file = 0;
        read = 0;

        file = fopen("/tmp/.pass", "r"); // /home/users/level03/.pass

        if (!file)
        {
                fwrite("ERROR: failed to open password file\n", 0x24, 1, stderr);
                exit(1);
        }
        read = fread(buffer2, 1, 0x29, file);
        buffer2[strcspn(buffer2, "\n")] = 0;
        if (read != 0x29)
        {
                fwrite("ERROR: failed to read password file\n", 0x24, 1, stderr);
                fwrite("ERROR: failed to read password file\n", 0x24, 1, stderr);
                exit(1);
        }
        fclose(file);
        puts("===== [ Secure Access System v1.0 ] =====");
        puts("/***************************************\\");
        puts("| You must login to access this system. |");
        puts("\\**************************************/");
        printf("--[ Username: ");

        fgets(buffer1, 0x64, stdin);
        buffer1[strcspn(buffer1, "\n")] = 0;

        printf("--[ Password: ");

        fgets(buffer3, 0x64, stdin);
        buffer3[strcspn(buffer3, "\n")] = 0;

        puts("*****************************************");
        if (strncmp(buffer2, buffer3, 0x29) == 0)
        {
                printf("Greetings, %s!\n", buffer1);
                system("/bin/sh");
                return(0);
        }
        printf(buffer1);
        puts(" does not have access!");
        exit(1);
}