#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"


u_int32_t *arr_a, *arr_x, *arr_dst;
int N = 128;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_x = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_dst = _mm_malloc(sizeof(u_int32_t) * N, 64);

    for(int i = 0; i < N; i++) {
        arr_a[i] = 1;
        arr_x[i] = 2;
        arr_dst[i] = 0;
    }
}

void foo(){

    __m128i a, x, dst;
	int b = 3;
    for( int i = 0; i < N; i+=NUM_32B_INT_IN_M128){

		a = _mm_load_si128((__m128i*)&arr_a[i]);
		x = _mm_load_si128((__m128i*)&arr_x[i]);
		dst = _mm_gf2p8affineinv_epi64_epi8 ( x, a, b);
		_mm_store_si128((__m128i*)&arr_dst[i], dst);
    }

	printf("a = ");
	print128_num_32( a);

	printf("x = ");
	print128_num_32( x);

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
