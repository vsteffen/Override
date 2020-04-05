// gcc -m32 ./test.c  -fstack-protector -z execstack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin() {
	char byte = 0;

	while (42) {
		byte = getchar();
		if (byte == '\n' || byte == -1)
			break ;
	}
}

int get_unum() {
	unsigned int nb;

	fflush(stdout);
	scanf("%u", &nb);
	clear_stdin();
	return (nb);
}

int store_number(char *buffer) {
	unsigned int nb = 0;
	unsigned int index = 0;

	printf(" Number: ");
	nb = get_unum();
	printf(" Index: ");
	index = get_unum();
	if (index % 3 == 0 || (nb >> 0x18) == 0xb7) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	*(unsigned int *)(buffer + index * 4) = nb;
	return (0);
}

int read_number(char *buffer) {
	unsigned int index;

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, *(unsigned int *)(buffer + index * 4));
	return (0);
}

int main(int ac, char **av, char **env) {

	char	buffer[0x190];
	char	buff_cmd[0x14] = {0};
	int	ret = 0;

	memset(buffer, 0, 0x190);
	while (*av) {
		memset(*av, 0, strlen(*av));
		av++;
	}
	while (*env) {
		memset(*env, 0, strlen(*env));
		env++;
	}
	puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n");
	while (1) {
		printf("Input command: ");
		ret = 1;
		fgets(buff_cmd, 0x14, stdin);
		buff_cmd[strlen(buff_cmd) - 1] = 0;
		if (strncmp(buff_cmd, "store", 0x5) == 0)
			ret = store_number(buffer);
		else if (strncmp(buff_cmd, "read", 0x4) == 0)
			ret = read_number(buffer);
		else if (strncmp(buff_cmd, "quit", 0x4) == 0)
			break;
		if (ret == 0)
			printf(" Completed %s command successfully\n", buff_cmd);
		else
			printf(" Failed to do %s command\n", buff_cmd);
	}
	return (0);
}
