# Level3 
This program asks the user for a password, converted to an int. This number is used in the function test which have a "if forest" of decrypt function call. If the value 0x1337d00d - password is less than 0x15, then, this result is used to get the index of a jump table and call decrypt. Decrypt is a function which use the result as a key to xor a buffer with predefined values and if this buffer is equal to "Congratulations!", it starts a shell with level04 permissions.

We can bruteforce all jump with this command:
```bash
for ((i=0; i<22; i++)); do let res=322424845-"$i";echo $res ; ./level03 <<< `echo  $res` ; done
```

The password "322424827" seems to be valid, we retry this one and we have shell !

The flag is **kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf**