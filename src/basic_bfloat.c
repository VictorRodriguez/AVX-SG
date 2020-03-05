/*
* References:
	* https://software.intel.com/en-us/articles/intel-advanced-vector-\
	extensions-512-intel-avx-512-new-vector-neural-network-instruction
	* https://en.wikichip.org/wiki/x86/avx512vnni
*/

#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdint.h>
#include "common.h"

#define MAXRAND 10

__m128 A,B,result;

void foo(int a, int b, int c){

	uint8_t arr_a[NUM_8B_INT_IN_M128];
	uint8_t arr_b[NUM_8B_INT_IN_M128];

	fill_array_uint8_t_128(arr_a,a);
	fill_array_uint8_t_128(arr_b,b);

	A = _mm_loadu_si128((__m128i*)&arr_a);
	B = _mm_loadu_si128((__m128i*)&arr_b);

	result = _mm_cvtne2ps_pbh(A,B);

}

int main(int argc, char **argv){

	srand((unsigned)time(NULL));
	int a =  (rand() % MAXRAND) + 1;
	int b =  (rand() % MAXRAND) + 1;
	int c =  (rand() % MAXRAND) + 1;

    foo(a,b,c);

/*
	printf("A = ");
	print128_num_8(A);

	printf("B = ");
	print128_num_8(B);

	printf("result = ");
	print128_num_16(result);

	printf("result_temp = ");
	print256_num_16(result_temp);
	print256_num_32(tmp);
*/

    return 0;
}
