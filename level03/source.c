#include <time.h>
#include <stdio.h>
#include <string.h>

void    decrypt(int key)
{
      	char	buffer[17];
	*(int *)(&buffer) = 0x757c7d51;
        *(int *)(&buffer + 4) = 0x67667360;
        *(int *)(&buffer + 8) = 0x7b66737e;
        *(int *)(&buffer + 12) = 0x33617c7d;
	buffer[16] = 0;
	unsigned int	size;
	unsigned int	i;

        size = strlen((char *)buffer);
        i  = 0;

	while (i < size)
	{
		buffer[i] = key ^ buffer[i];
		i += 1;
	}
	if (strncmp("Congratulations!", buffer, sizeof("Congratulations!")) == 0)
	{
		system("/bin/bash");
		return ;
	}
	puts("\nInvalid password");
}

void    test(int input, int value) {
        unsigned int key;

        key = value - input;
        if (key < 0x16)
        {
                key <<= 2;
                key += 0x80489f0; // At this address in the real binary, there's a const table containing the addresses of all the following decrypt call

                // ((void (*)())*(unsigned int *)key)(); same as asm but no jmp \ call

                asm(
                        "mov %eax, -0xc(%ebp)\n"
                        "mov (%eax), %eax\n"
                        "jmp *%eax\n"
                );

                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
                decrypt(key);
                asm("jmp end_test");
        }
        decrypt(rand());
        asm("end_test:");
        return ;
}

int main(int ac, char **av) {
        int buffer;

        srand(time(NULL));
        puts("***********************************");
        puts("*\t\tlevel03\t\t**");
        puts("***********************************");
        printf("Password:");
        scanf("%d", &buffer);
        test(buffer, 0x1337d00d);
        return (0);
}