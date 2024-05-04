./a.out
nasm -f elf64 output.asm -o output.o

if [ $? -ne 0 ];  then
    echo "Not compiling output"
    exit 1
fi

nasm -f elf64 print_digit.asm  -o print.o

if [ $? -ne 0 ]; then
    echo "Not compiling print"
    exit 1 
fi


echo Compiling success

ld  print.o output.o -o output

if [ $? -ne 0 ]; then
    echo "Not Linking"
    exit 1
fi
echo Linking success
./output
echo Status code: $?
echo Run success

exit 0