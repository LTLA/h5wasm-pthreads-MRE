#!/bin/bash

failures=0
for x in {1..200}
do
    if [ $(($x % 10)) -eq 0 ]
    then
        echo "Iteration $x"
    fi
    node --experimental-vm-modules --experimental-wasm-threads --experimental-wasm-bulk-memory --experimental-wasm-bigint index.js
    if [ $? -gt 0 ]
    then
        failures=$(($failures + 1))
    fi
done  

echo "$failures out of 200 failed"
