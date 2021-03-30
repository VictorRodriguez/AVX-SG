#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


float a[256] = {0}; 
float b[256] = {0};
float c[256] = {0};

void foo(){
    __m512 result,B,C;
        for (int i=0; i<256; i+=16){
            B =  _mm512_load_ps(&b[i]);
            C =  _mm512_load_ps(&c[i]);
            result = _mm512_add_ps(B,C);
            _mm512_store_ps(&a[i], result);
        }
}

void fill_arrays(){
    for (int i=0; i<256; i++){
        b[i] = 1.0;
        c[i] = 2.0;

    }
}

int check_arrays(){
    int ret = 0;
    for (int i=0; i<256; i++){
        if (a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            break;
    }
    return ret;
}


int main(int argc, char **argv){
    if (__builtin_cpu_supports ("avx512f")){
        // initialize arrays
        fill_arrays();
        foo();
        if (check_arrays())
            return -1;
        printf("Works !!!\n");
        return 0;
    }
    else{
        printf("SKIP: instructions not supproted\n");
        return -1;
    }
}
