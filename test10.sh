#!/bin/bash 

g++ main.cpp MyVector.cpp -o main 2> /dev/null
./main > "Test/output.txt"

if ! diff "Test/output.txt" "Test/expected.txt" > /dev/null; then
    echo "Test : FAIL"
else
    echo "Test : PASS"
fi
