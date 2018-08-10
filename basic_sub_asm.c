#include <stdio.h>

int main() {

    int arg1,arg2,sub;

    arg1 = 2;
    arg2 = 1;
    __asm__ ( "subl %%ebx, %%eax;" : "=a" (sub) : "a" (arg1) , "b" (arg2) );

    printf( "%d - %d = %d\n", arg1, arg2, sub );

    if (sub == 1){
        printf("Works!!\n");
        return 0;
    } else {
        printf("FAIL!!\n");
        return -1;
    }
}
