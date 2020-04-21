// gcc level09.c -fno-stack-protector -fpic -pie

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_mail {
	char	msg[0x8c];
	char	username[0x28];
	int	msg_len;
};

void	secret_backdoor() {
	char	command[0x80];

	fgets(command, 0x80, stdin);
	system(command);
}

void	set_msg(struct s_mail *mail) {
	char buffer_set_msg[0x400];

	memset(buffer_set_msg, 0, sizeof(buffer_set_msg));
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(buffer_set_msg, sizeof(buffer_set_msg), stdin);
	strncpy(mail->msg, buffer_set_msg, mail->msg_len);
}

void    set_username(struct s_mail *mail) {
	int	len;
	char	name[0x80];

	memset(name, 0, 0x80);
	puts(">: Enter your username");
	printf( ">>: ");
	fgets(name, 0x80, stdin);
	len = 0;
	while (len < 0x29 && name[len]) {
		mail->username[len] = name[len];
		len +=1;
	}
	printf(">: Welcome, %s", mail->username);
}

void    handle_msg() {
	struct s_mail mail;

	memset(mail.username, 0, sizeof(mail.username));
	mail.msg_len = 0x8c;
	set_username(&mail);
	set_msg(&mail);

	puts(">: Msg sent!");
}

int main() {
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------\n");
	handle_msg();
	return (0);
}
