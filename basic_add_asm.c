#include <stdio.h>

int main() {

    int arg1,arg2,add;

    arg1=1;
    arg2=2;

    /* Perform Addition */
    __asm__ ( "addl %%ebx, %%eax;" : "=a" (add) : "a" (arg1) , "b" (arg2) );

    printf( "%d + %d = %d\n", arg1, arg2, add );

    if (add == 3){
        printf("Works!!\n");
        return 0;
    } else {
        printf("FAIL!!\n");
        return -1;
    }
}
