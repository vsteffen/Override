#!/bin/bash

for((i=0;i<100;i++)); do ./level02 < <(python -c "print('AAAA'  + '%$i"'$'"p\nBBBBBBBB' )") ; done | grep 'does not have access!' | sed -n '/42424242/,/41414141/p'