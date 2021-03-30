#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"


u_int32_t *arr_a, *arr_b, *arr_c, *arr_dst;
int N = 128;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_b = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_c = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_dst = _mm_malloc(sizeof(u_int32_t) * N, 64);
    for(int i = 0; i < N; i++) {
        arr_a[i] = 1;
        arr_b[i] = 2;
        arr_c[i] = 3;

        arr_dst[i] = 0;
    }
}

void foo(){

    __m128i a, b, c, dst;

    for( int i = 0; i < N; i+=NUM_32B_INT_IN_M128){

		a = _mm_load_si128((__m128i*)&arr_a[i]);
		b = _mm_load_si128((__m128i*)&arr_b[i]);
		c = _mm_load_si128((__m128i*)&arr_c[i]);

        dst = _mm_madd52hi_epu64 (a, b, c);
		_mm_store_si128((__m128i*)&arr_dst[i], dst);
    }

	printf("a = ");
	print128_num_32( a);

	printf("b = ");
	print128_num_32( b);

	printf("c = ");
	print128_num_32( c);

	printf("dst = ");
	print128_num_32( dst);

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
