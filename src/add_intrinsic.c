/*
 * =====================================================================================
 *
 *       Filename:  add_intrinsic.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2018 05:28:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Victor Rodriguez (), vm.rod25@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <immintrin.h>
#include "add.h"

float a[256] = {0}; 
float b[256] = {0};
float c[256] = {0};

void foo(){
    __m256 result,B,C;
        for (int i=0; i<256; i+=8){
            B =  _mm256_load_ps(&b[i]);
            C =  _mm256_load_ps(&c[i]);
            result = _mm256_add_ps(B,C);
            for ( int j=0;j<8;j++){
                a[i+j] = result[j];
            }
        }
}


int main(){

    for (int i=0; i<256; i++){
        b[i] = 1.0;
        c[i] = 2.0;

    }

    for (int x=0; x<MAX; x++){
        foo();
    }

    for (int i=0; i<256; i++){
        if (a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            return -1;
    }
    return 0;
}
