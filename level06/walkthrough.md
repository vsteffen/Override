# Level 6

The program here ask for a name, and a serial in the main function, the main also check with ptrace if the executable is already traced, if it is, then exit the program, if not, it calls function auth with name and serial as arguments.

Function auth verify if the name is at least 5char long, and if the char in it are printable (char > 1f). Then it creates a key with the 3rd char in name, and change it in a loop as big as the lenght of the name. After that it compares the result with the serial given, if they are equal return 0, else return 1.

In the main if the result of the call to auth is equal to 0, then call sytem with /bin/sh.

To find out the right serial, with a name, with entered in gdb.
When ptrace is call we must change its result because we already are executing the program, and without changing it, it would exit.
After that, we just have to go at the end of the auth function, and see with what our serial is compared. Then take this int, convert it in decimal and re run the program with the name and the int found.

```bash
=> 0x80487ba <auth+114>:	cmp    eax,0xffffffff
   0x80487bd <auth+117>:	jne    0x80487ed <auth+165>
   0x80487bf <auth+119>:	mov    DWORD PTR [esp],0x8048a68
   0x80487c6 <auth+126>:	call   0x8048590 <puts@plt>
   0x80487cb <auth+131>:	mov    DWORD PTR [esp],0x8048a8c
   0x80487d2 <auth+138>:	call   0x8048590 <puts@plt>
   0x80487d7 <auth+143>:	mov    DWORD PTR [esp],0x8048ab0
   0x80487de <auth+150>:	call   0x8048590 <puts@plt>

Breakpoint 1, 0x080487ba in auth ()
gdb$ set $eax=1

=> 0x8048866 <auth+286>:	cmp    eax,DWORD PTR [ebp-0x10]
   0x8048869 <auth+289>:	je     0x8048872 <auth+298>
   0x804886b <auth+291>:	mov    eax,0x1
   0x8048870 <auth+296>:	jmp    0x8048877 <auth+303>
   0x8048872 <auth+298>:	mov    eax,0x0
   0x8048877 <auth+303>:	leave  
   0x8048878 <auth+304>:	ret    
   0x8048879 <main>:	push   ebp

Breakpoint 2, 0x08048866 in auth ()
gdb$ x/wx $ebp-0x10
0xffffd6a8:	0x005f1afa
gdb$ p/d 0x005f1afa
$1 = 6232826
```

# for exemple :

```
Vivien
6232826

Maelyss
6233774 //0x005f1eae
```

```bash
level06@OverRide:/home/users/level06$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: Vivien
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6232826
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
The flag is **GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8**
