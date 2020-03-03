// gcc -fno-stack-protector -z execstack -m32

#include <string.h>
#include <stdio.h>

char    a_user_name[100];

int verify_user_pass(char *buff)
{
        return (strncmp(buff, "admin", 0x5));
}

int verify_user_name()
{
        puts("verifying username....\n");
        return (strncmp(a_user_name, "dat_wil", 0x7));
}

int main() {
        char buff[0x40];
        int diff;

        memset(buff, 0, 0x40);
        diff = 0;
        puts("********* ADMIN LOGIN PROMPT *********");
        printf("Enter Username: ");
        fgets(a_user_name, 0x100, stdin);
        diff = verify_user_name();
        if (diff != 0)
        {
                puts("nope, incorrect username...\n");
                return (1);
        }
        puts("Enter Password: ");
        fgets(buff, 0x64, stdin);
        diff = verify_user_pass(buff);
        if (diff != 0)
        {
                if (diff != 0)
                {
                        puts("nope, incorrect password...\n");
                        return (1);
                }
        }
        return (0);
}
