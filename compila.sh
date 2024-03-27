
# cleanup
rm -f *.o main.neo main.map neo6502.lib{,.temp}

#compile
#/Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/bin/mos-neo6502-clang -Os -v -fverbose-asm -mcpu=mosw65c02 -D__NEO6502__ -mlto-zp=224 \
#-I /Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/mos-platform/neo6502/asminc \
#-L /Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/mos-platform/neo6502/lib \
#-isystem Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/mos-platform/neo6502/include \
#main.c utility.c api.c quicksort.c sprite.c -o main.neo 
#-v -fverbose-asm

/Users/giovanni.pozzobon/Documents/GitHub/llvm-mos-sdk/bin/mos-neo6502-clang -Os  main.c api.c quicksort.c sprite.c -o main.neo 


# launch emulator
test -f main.neo && ./neo main.neo@800 cold