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

__m128i A,B,result;
__m256i result_temp,ones_tmp,tmp;

void foo(int a, int b, int c){

	uint8_t arr_a[NUM_8B_INT_IN_M128];
	uint8_t arr_b[NUM_8B_INT_IN_M128];

    for (int i=0; i<NUM_8B_INT_IN_M128; i++){
        arr_a[i] = (uint8_t)a;
        arr_b[i] = (uint8_t)b;
	}


	A = _mm_loadu_si128((__m128i*)&arr_a);
	B = _mm_loadu_si128((__m128i*)&arr_b);

	/*
	Using the foundation AVX-512, for 16-bit, this is possible using two
	instructions - VPMADDWD which is used to multiply two 16-bit pairs and add
	them together followed a VPADDD which adds the accumulate value.

	Likewise, for 8-bit values, three instructions are needed - VPMADDUBSW
	which is used to multiply two 8-bit pairs and add them together, followed by a
	VPMADDWD with the value 1 in order to simply up-convert the 16-bit values to
	32-bit values, followed by the VPADDD instruction which adds the result to an
	accumulator.
	*/
	result = _mm_maddubs_epi16(A,B);
	result_temp =_mm256_setr_m128i(result,result);

	uint16_t tmp_array[NUM_16B_INT_IN_M256];
    for (int i=0; i<NUM_16B_INT_IN_M256; i++){
        tmp_array[i] = (uint16_t)1;
	}
	ones_tmp = _mm256_loadu_si256((__m256i*)&tmp_array);
	tmp = _mm256_madd_epi16(result_temp,ones_tmp);

}

int main(int argc, char **argv){

	srand((unsigned)time(NULL));
	int a =  (rand() % MAXRAND) + 1;
	int b =  (rand() % MAXRAND) + 1;
	int c =  (rand() % MAXRAND) + 1;

    foo(a,b,c);

	printf("A = ");
	print128_num_8(A);

	printf("B = ");
	print128_num_8(B);

	printf("result = ");
	print128_num_16(result);

	printf("result_temp = ");
	print256_num_16(result_temp);
	print256_num_32(tmp);
    return 0;
}
