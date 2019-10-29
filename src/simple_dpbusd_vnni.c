/*
* References:
	* https://software.intel.com/en-us/articles/intel-advanced-vector-extensions-512-intel-avx-512-new-vector-neural-network-instruction
	* https://en.wikichip.org/wiki/x86/avx512vnni

*/

#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdint.h>

#define MAXRAND 10
#define N_8 16
#define N_16 8
#define N_32 4


void print128_num_32(__m128i var) {
    uint32_t *val = (uint32_t*) &var;
	for(int i = 0; i < N_32; i++)
		printf("%i ",val[1]);
	printf("\n");
}
void print128_num_16(__m128i var){
    uint16_t *val = (uint16_t*) &var;
	for(int i = 0; i < N_16; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void print128_num_8(__m128i var){
    uint8_t *val = (uint8_t*) &var;
	for(int i = 0; i < N_8; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void foo(int a, int b, int c){

	uint8_t arr_a[N_8];
	uint8_t arr_b[N_8];
	uint32_t arr_src[N_32];

    for (int i=0; i<N_8; i++){
        arr_a[i] = (uint8_t)a;
        arr_b[i] = (uint8_t)b;
	}

    for (int i=0; i<N_32; i++){
        arr_src[i] = c;
	}
    __m128i A,B,src,result;

	A = _mm_loadu_si128((__m128i*)&arr_a);
	B = _mm_loadu_si128((__m128i*)&arr_b);
	src = _mm_loadu_si128((__m128i*)&arr_src);

	// test basic _mm_add_epi16
	//result = _mm_add_epi16(A,B);

	// test basic _mm_maddubs_epi16
	// Vertically multiply two 8-bit integers,
	// then horizontally add adjacent pairs of 16-bit integers
	//result = _mm_maddubs_epi16(A,B);

	// PERFORM THE DOT PRODUCT OPERATION USING FUSED INSTRUCTION
	result =  _mm_dpbusds_epi32(src,A,B);

	printf("A = ");
	print128_num_8(A);

	printf("B = ");
	print128_num_8(B);

	printf("src = ");
	print128_num_32(src);

	printf("result = ");
	print128_num_32(result);

}

int main(int argc, char **argv){

	srand((unsigned)time(NULL));
	int a =  (rand() % MAXRAND) + 1;
	int b =  (rand() % MAXRAND) + 1;
	int c =  (rand() % MAXRAND) + 1;

    foo(a,b,c);

    return 0;
}
