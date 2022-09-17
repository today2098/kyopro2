#!/bin/bash

# Terminate for error.
function terminate_execution () {
    echo 'Terminate execution.'
    exit 1
}


# Check number of arguments.
if (( "$#" != 2 )); then
    echo 'Number of arguments is wrong.';
    terminate_execution
fi


# Check necessary files.
flag=false
for file in "$1" "$2" "make_random_case.cpp"; do
    if [[ ! -e "$file" ]]; then
        echo "$file does not exist."
        flag=true
    fi
done

if "$flag"; then
    terminate_execution
fi


# Compile.
g++ "$1" -o "a.out"
if (( "$?" != 0 )); then
    echo "Fail in compiling $1."
    terminate_execution
fi

g++ "$2" -o "b.out"
if (( "$?" != 0 )); then
    echo "Fail in compiling $2."
    terminate_execution
fi

g++ "make_random_case.cpp" -o "c.out"
if (( "$?" != 0 )); then
    echo "Fail in compiling make_random_case.cpp."
    terminate_execution
fi


# Test random cases by two ways until the two answers are not same.
for (( i=0; i < 50; ++i )) {
    ./c.out > input.txt
    ans1=$(./a.out < input.txt)
    ans2=$(./b.out < input.txt)
    
    if [[ "$ans1" != "$ans2" ]]; then
        echo 'Different Answer!'
        echo ''
        
        if (( $(wc -c < input.txt) <= 10000 )); then
            echo '[IN]'
            cat input.txt
            echo ''
        fi
        
        echo '[OUT a]'
        echo "${ans1}"
        echo ''
        echo '[OUT b]'
        echo "${ans2}"
        exit
    fi
}

echo 'Finish testing 50 times.'
