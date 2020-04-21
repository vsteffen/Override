// gcc ./source.c -m32 -fno-stack-protector
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <string.h>

int main(int ac, char **av) {
        pid_t   child;          // 0xac
        int     val_int0;       // 0xa8
        int     status_child;   // 0x1c
        char    buffer[0x80];   // 0x20

        child = fork();
        memset(buffer, 0, sizeof(buffer));
        val_int0 = 0;
        status_child = 0;
        if (child == 0) {
                prctl(1, 1);
                ptrace(0, 0, 0, 0);
                puts("Give me some shellcode, k");
                return ((int)gets(buffer));
        }
        else {
                while (42) {
                        wait(&status_child);
                        if (WIFEXITED(status_child) || WIFSIGNALED(status_child)) {
				puts("child is exiting...");
				break ;
			}
			else {
				val_int0 = ptrace(PTRACE_PEEKUSER, child, 0x2c, 0);
                                if (val_int0 == 0xb) {
                                	puts("no exec() for you");
                                        kill(child, SIGKILL);
                                        break ;
                                }
                        }
                }
        }
        return (0);
}
