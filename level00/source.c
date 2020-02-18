// gcc source.c -fno-stack-protector -m32

#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int a;

	puts("***********************************");
	puts("* 	     -Level00 -		  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &a);
	if (a == 0x149c)
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
		return(0);
	}
	puts("\nInvalid Password!");
	return(1);
}
