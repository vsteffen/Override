// gcc level08.c -fstack-protector -z execstack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_wrapper(FILE *stream, char *msg, char *file) {
	char buffer[0x100];

	strcpy(buffer, msg);
	snprintf(buffer + strlen(buffer), 0xfe - strlen(buffer), file);
	buffer[strcspn(buffer, "\n")] = 0;
	fprintf(stream, "LOG: %s\n", buffer);
}
 
int main(int ac, char **av) {
	char	buffer[0x60];
	FILE	*stream1;
	FILE	*stream2;
	int	fd = -1;
	char	c = -1;

	if (ac != 2)
		printf("Usage: %s filename\n", *av);
	stream1 = fopen("./backups/.log", "w");
	if (stream1 == 0) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(stream1, "Starting back up: ", av[1]);
	stream2 = fopen(av[1], "r");
	if (stream2 == 0) {
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}

	strncat(memcpy(buffer, "./backups/", 10), av[1], strlen(av[1]));
	
	if ((fd = open(buffer, 0xc1, 0x1b0)) == 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
		exit(1);
	}
	while (1) {
		write(fd, &c, 1);
		c = fgetc(stream2);
		if (c == -1)
			break;
	}
	log_wrapper(stream1, "Finished back up ", av[1]);
	fclose(stream2);
	close(fd);
	return (0);
}