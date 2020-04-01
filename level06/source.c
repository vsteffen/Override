//-gcc level06.c -o level06 -fno-stack-protector -z execstack -m32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth(char *buffer, unsigned int serial)
{
    int key;
    int i;
    int size;

    buffer[strcspn(buffer, "/n")] = 0;
    if ((size = strnlen(buffer, 0x20)) <= 0x5)
    {
        return(1);
    }
    if (ptrace(0, 0, 1, 0) == -1)
    {
        puts("\33[32m.---------------------------.");
        puts("\33[31m| !! TAMPERING DETECTED !!  |");
        puts("\33[32m.---------------------------.");
        return (1);
    }
    key = (int)buffer[0x3] ^ 0x1337 + 0x5eeded;
    i = 0;
    while (i < size)
    {
        if (buffer[i] <= 0x1f)
        {
            return (1);
        }
        //modifying key

        0x08048823 <+219>:	mov    -0x14(%ebp),%eax     //
        0x08048826 <+222>:	add    0x8(%ebp),%eax       //
        0x08048829 <+225>:	movzbl (%eax),%eax          //
        0x0804882c <+228>:	movsbl %al,%eax             // (int)buffer[i]
        0x0804882f <+231>:	mov    %eax,%ecx
        0x08048831 <+233>:	xor    -0x10(%ebp),%ecx     // xor with key
        0x08048834 <+236>:	mov    $0x88233b2b,%edx
        0x08048839 <+241>:	mov    %ecx,%eax
        0x0804883b <+243>:	mul    %edx
        0x0804883d <+245>:	mov    %ecx,%eax
        0x0804883f <+247>:	sub    %edx,%eax
        0x08048841 <+249>:	shr    %eax
        0x08048843 <+251>:	add    %edx,%eax
        0x08048845 <+253>:	shr    $0xa,%eax
        0x08048848 <+256>:	imul   $0x539,%eax,%eax
        0x0804884e <+262>:	mov    %ecx,%edx
        0x08048850 <+264>:	sub    %eax,%edx
        0x08048852 <+266>:	mov    %edx,%eax
        0x08048854 <+268>:	add    %eax,-0x10(%ebp)     // saving  result in key

        i += 1;
    }
    if (key == serial)
        return (0);
    return(1);
}

int main() {
    char buffer[0x20];
    unsigned int serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(buffer, 0x20, stdin);
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    scanf("%u", &serial);
    if (auth(buffer, serial) == 0)
    {
        puts("Authenticated!");
        system("/bin/sh");
        return(0);
    }
    return(1);
}