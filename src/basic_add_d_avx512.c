#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


double a[256] = {0};
double b[256] = {0};
double c[256] = {0};

void foo(){
    __m512d result,B,C;
        for (int i=0; i<256; i+=8){
            B =  _mm512_load_pd(&b[i]);
            C =  _mm512_load_pd(&c[i]);
            result = _mm512_add_pd(B,C);
            _mm512_store_pd(&a[i], result);
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
            printf("%f\n",a[i]);
            printf("%d\n",i);
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
        printf("Works!!\n");
        return 0;
    }
    else{
        printf("SKIP: instructions not supproted\n");
        return -1;
    }
}
