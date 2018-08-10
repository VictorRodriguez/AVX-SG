#include <stdio.h>

int main() {

    int arg1, arg2,mul;

    arg1 = 2;
    arg2 = 1;

    __asm__ ( "imull %%ebx, %%eax;" : "=a" (mul) : "a" (arg1) , "b" (arg2) );

    printf( "%d * %d = %d\n",arg1,arg2,mul);

    if (mul == 2){
        printf("Works!!\n");
        return 0;
    } else {
        printf("FAIL!!\n");
        return -1;
    }
}
