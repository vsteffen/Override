# Level09

This program send a fake message. To send it, it use a struct with a buffer for the message, one for the username and the length of the buffer of message:
```c
struct s_mail {
	char	msg[0x8c];
	char	username[0x28];
	int	msg_len;
};
```

These buffers will be fill with 'set_username' and 'set_msg'.

In the function 'set_username', a local buffer of 0x80 bytes is used to store the username. Then, 0x29 bytes of this local buffer are copied to the buffer of username in the struct. Since the buffer of username in the struct is 0x28 bytes long, 1 byte is copied after and will replace the value of the message length.

In the function 'set_msg', a local buffer of 0x400 bytes is used to store the message of the user and 'strncpy' will use the value of the message length in the struct to fill the buffer of message inside the struct. This means that we can use a buffer overflow to rewrite the old eip of 'handle_msg' !

To rewrite old eip, we need to write a username of 0x28 characters, the length to overflow and rewrite old eip (sizeof(struct s_mail) + padding + old ebp + old eip -> 0xd0), use a newline for the end of the buffer, fill the memory until the new address of old eip.

For the new address, there's a hidden function which is called 'secret_backdoor'. It read a command on stdin and use it for the 'system' call. For the buffer overflow, we will use the address of this function (0x000055555555488c) to exploit this binary. The payload is :

```bash
cat  <(python -c 'print("a" * 0x28 + "\xd0" + "\n" + "a" * 0xc8 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "/bin/bash")') - | /home/users/level09/level09
```

The flag is **j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE**
