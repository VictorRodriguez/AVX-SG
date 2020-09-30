#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


u_int32_t *arr_a, *arr_b, *arr_c, *arr_dst;
int N = 256;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_b = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_c = _mm_malloc(sizeof(u_int32_t) * N, 64);
    for(int i = 0; i < N; i++) {
        arr_a[i] = 1;
        arr_b[i] = 2;
        arr_b[i] = 3;
    }
}

void foo(){

    __m128i a, b, c, dst;

    for( int i = 0; i < N; i+=4){

		a = _mm_load_si128((__m128i*)&arr_a[i]);
		b = _mm_load_si128((__m128i*)&arr_b[i]);
		c = _mm_load_si128((__m128i*)&arr_c[i]);

        dst = _mm_madd52hi_epu64 (a, b, c);

		_mm_store_si128((__m128i*)&arr_dst[i], dst);
    }
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

    if (__builtin_cpu_supports ("avx512f")){
        // initialize arrays
        fill_arrays();
        foo();
        //if (check_result())
        //    return -1;
        printf("Works!!\n");
        return 0;
    }
    else{
        printf("SKIP: instructions not supproted\n");
        return -1;
    }
}
