#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"


u_int32_t *arr_a, *arr_x, *arr_dst;
int N = 256;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_x = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_dst = _mm_malloc(sizeof(u_int32_t) * N, 64);

    for(int i = 0; i < N; i++) {
        arr_a[i] = 2;
        arr_x[i] = 3;
        arr_dst[i] = 0;
    }
}

void foo(){

    __m256i a, RoundKey, dst;
    for( int i = 0; i < N; i+=NUM_32B_INT_IN_M256){

		a = _mm256_loadu_si256((__m256i*)&arr_a[i]);
		RoundKey = _mm256_loadu_si256((__m256i*)&arr_x[i]);
		dst = _mm256_aesdec_epi128 (a, RoundKey);
		_mm256_store_si256 ((__m256i*)&arr_dst[i], dst);
    }

	printf("a = ");
	print256_num_32( a);

	printf("x = ");
	print256_num_32( RoundKey);

	printf("dst = ");
	print256_num_32( dst);

	printf("\n");
	for (int x; x < N; x ++)
		printf("%u ",arr_dst[x]);
	printf("\n");

}


int main(int argc, char **argv){

    if (__builtin_cpu_supports ("avx512f")){
        fill_arrays();
        foo();
	}
	return 0;
}
