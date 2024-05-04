#! /bin/sh

nasm -f elf64 source/$1.asm -o $1.o

if [ $? -ne 0 ];  then
    echo "Not compiling $1"
    exit 1
fi

nasm -f elf64 print_digit.asm  -o print.o

if [ $? -ne 0 ]; then
    echo "Not compiling print"
    exit 1 
fi


echo Compiling success

ld  print.o $1.o -o $1

if [ $? -ne 0 ]; then
    echo "Not Linking"
    exit 1
fi
echo Linking success
./$1
echo Status code: $?
echo Run success

exit 0
