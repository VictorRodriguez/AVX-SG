#include <stdio.h>

int main() {

    int arg1, arg2,quo, rem ;

    arg1 = 10;
    arg2 = 3;

    __asm__ ( "movl $0x0, %%edx;"
        "movl %2, %%eax;"
        "movl %3, %%ebx;"
        "idivl %%ebx;" : "=a" (quo), "=d" (rem) : "g" (arg1), "g" (arg2) );

    printf( "%d / %d = %d\n", arg1, arg2, quo );
    printf( "%d %% %d = %d\n", arg1, arg2, rem );
    if (quo == 3 && rem == 1){
        printf("Works!!\n");
        return 0;
    } else {
        printf("FAIL!!\n");
        return -1;
    }
}
