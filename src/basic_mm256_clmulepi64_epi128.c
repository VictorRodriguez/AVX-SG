#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"


u_int32_t *arr_b, *arr_c, *arr_dst;
int N = 256;

void fill_arrays(){
    arr_b = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_c = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_dst = _mm_malloc(sizeof(u_int32_t) * N, 64);

    for(int i = 0; i < N; i++) {
        arr_b[i] = 2;
        arr_c[i] = 3;
        arr_dst[i] = 0;
    }
}

void foo(){

    __m256i b, c, dst;
	const int Imm8 = 3;
    for( int i = 0; i < N; i+=NUM_32B_INT_IN_M256){

		b = _mm256_loadu_si256((__m256i*)&arr_b[i]);
		c = _mm256_loadu_si256((__m256i*)&arr_c[i]);
		dst = _mm256_clmulepi64_epi128 ( b, c, Imm8);
		_mm256_store_si256 ((__m256i*)&arr_dst[i], dst);
    }

	printf("b = ");
	print256_num_32(b);

	printf("c = ");
	print256_num_32(c);

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
