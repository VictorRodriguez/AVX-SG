#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


u_int32_t *arr_a, *arr_b, *arr_c, *arr_d,*arr_result;
int N = 256;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_b = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_c = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_d = _mm_malloc(sizeof(u_int32_t) * N, 64);

    for(int i = 0; i < N; i++) {
        arr_a[i] = 1;
        arr_b[i] = 2;
        arr_c[i] = 1;
        arr_d[i] = 2;
    }
}

void foo(){

    __m128i values = _mm_setr_epi32(0x1234, 0x2345, 0x3456, 0x4567);
    values = _mm_dpbusd_epi32(values, values, values);
    printf("%d",values[0]);
}

int check_result(){

    int ret = 0;
    for (int i=0; i<N; i++){
        if (arr_c[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            printf("%d\n",arr_c[i]);
            break;
    }
    return ret;
}

int main(int argc, char **argv){

        // initialize arrays
        fill_arrays();
        foo();
        if (check_result())
            return -1;
        printf("Works!!\n");
        return 0;
}
