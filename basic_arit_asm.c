#include <stdio.h>

int main() {

    int arg1, arg2, add, sub, mul, quo, rem ;

    arg1 = 100000;
    arg2 = 232;
//    printf( "Enter two integer numbers : " );
//    scanf( "%d%d", &arg1, &arg2 );

    int i,j;

    for ( i = 0 ; i < 100 ; i++){
    for ( j = 0 ; j < 100 ; j++){
    /* Perform Addition, Subtraction, Multiplication & Division */
    __asm__ ( "addl %%ebx, %%eax;" : "=a" (add) : "a" (arg1) , "b" (arg2) );
    __asm__ ( "subl %%ebx, %%eax;" : "=a" (sub) : "a" (arg1) , "b" (arg2) );
    __asm__ ( "imull %%ebx, %%eax;" : "=a" (mul) : "a" (arg1) , "b" (arg2) );

    __asm__ ( "movl $0x0, %%edx;"
              "movl %2, %%eax;"
              "movl %3, %%ebx;"
               "idivl %%ebx;" : "=a" (quo), "=d" (rem) : "g" (arg1), "g" (arg2) );
    }}
/*
    if (arg1 + arg1 != add)
        printf("FAIL\n"); return -1;
    if (arg1 - arg2 != sub)
        printf("FAIL\n"); return -1;
    if (arg1 * arg1 != mul)
        printf("FAIL\n"); return -1;
    if (arg1 / arg1 != quo)
        printf("FAIL\n"); return -1;
    if (arg1 % arg1 != rem)
        printf("FAIL\n"); return -1;
*/
    printf( "%d + %d = %d\n", arg1, arg2, add );
    printf( "%d - %d = %d\n", arg1, arg2, sub );
    printf( "%d * %d = %d\n", arg1, arg2, mul );
    printf( "%d / %d = %d\n", arg1, arg2, quo );
    printf( "%d %% %d = %d\n", arg1, arg2, rem );

    return 0 ;
}
