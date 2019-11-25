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

#define MAXRAND 10
#define NUM_8B_INT_IN_M128  (sizeof(__m128i)/sizeof(uint8_t))
#define NUM_16B_INT_IN_M128 (sizeof(__m128i)/sizeof(uint16_t))
#define NUM_32B_INT_IN_M128 (sizeof(__m128i)/sizeof(uint32_t))


void print128_num_32(__m128i var) {
    uint32_t *val = (uint32_t*) &var;
	for(int i = 0; i < NUM_32B_INT_IN_M128; i++)
		printf("%i ",val[1]);
	printf("\n");
}
void print128_num_16(__m128i var){
    uint16_t *val = (uint16_t*) &var;
	for(int i = 0; i < NUM_16B_INT_IN_M128; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void print128_num_8(__m128i var){
    uint8_t *val = (uint8_t*) &var;
	for(int i = 0; i < NUM_8B_INT_IN_M128; i++)
		printf("%i ",val[1]);
	printf("\n");
}

__m128i A,B,result;

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
	Vertically multiply each unsigned 8-bit integer from a with the
	corresponding signed 8-bit integer from b, producing intermediate signed
	16-bit integers. Horizontally add adjacent pairs of intermediate signed
	16-bit integers, and pack the saturated results in dst.
	*/
	result = _mm_maddubs_epi16(A,B);

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

    return 0;
}
