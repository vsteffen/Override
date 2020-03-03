char	a_user_name[0x100];

int verify_user_pass(char *buff)
{
	return (memcmp(buff, "admin", 0x5));
}

int verify_user_name()
{
	puts("verifying username....\n");
	return (memcmp(a_user_name, "dat_wil", 0x7));
}

int main() {
	char buff[0x40];
	int diff;

	memset(buff, 0, 0x40);
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 0x100, STDIN);
	diff = verify_user_name();
	if (diff != 0)
	{
		puts("nope, incorrect username...\n");
		return (1);
	}
	puts("Enter Password: ");
	fgets(buff, 0x64, STDIN);
	diff = verify_user_pass(buff);
	if (diff == 0)
	{
		puts("nope, incorrect password...\n");
		return (1);
	}
	return (0);
}
