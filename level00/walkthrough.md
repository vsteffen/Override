# Level0
We can see in the source code of this program that it use scanf with "%d" and the address of an int allocated in the stack. If this value equal to 0x149c (5276), system is called with "/bin/sh". Otherwise, the program return.

The payload is simply:
```bash
./level00 <<< 5276
```
Flag is **uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL**
