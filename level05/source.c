#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char	buffer[0x64];
	int	size;

	size = 0;
	fgets(buffer, 0x64, stdin);
	size = 0;
	while (size < strlen(buffer))
	{
		if (buffer[size] > 0x40) {
			if (buffer[size] <= 0x5a) {
				buffer[size] = buffer[size] ^ 0x20;
			}
		}
		size += 1;
	}
	printf(buffer);
	exit(0);
}
