#!/bin/bash

PASSWORD=""
for uint64_t in "756e505234376848" "45414a3561733951" "377a7143574e6758" "354a35686e475873" "48336750664b394d"
do
	echo -n "$uint64_t" | xxd -r -p | rev
	PASSWORD+=`echo -n "$uint64_t" | xxd -r -p | rev`
done

echo "Password is -> $PASSWORD"