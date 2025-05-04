gcc -shared -o random1.so random1.c
gcc -o random1_loader random1_loader.c -L. -l:random1.so 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`
./random1_loader
