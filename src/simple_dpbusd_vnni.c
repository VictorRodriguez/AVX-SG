#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdint.h>

#define MAXRAND 100
#define N 16


void print128_num_32(__m128i var)
{
    uint32_t *val = (uint32_t*) &var;
    printf("Numerical: %i %i %i %i \n",
           val[0], val[1], val[2], val[3]);
}
void print128_num_16(__m128i var)
{
    uint16_t *val = (uint16_t*) &var;
    printf("Numerical: %i %i %i %i %i %i %i %i \n",
           val[0], val[1], val[2], val[3], val[4], val[5],
           val[6], val[8]);
}

void print128_num_8(__m128i var)
{
    uint8_t *val = (uint8_t*) &var;
    printf("Numerical: %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i \n",
           val[0], val[1], val[2], val[3], val[4], val[5],
           val[6], val[7], val[8], val[9], val[10], val[11],
           val[12], val[13], val[14], val[15]);
}

void foo(){

	uint8_t arr_a[N];
	uint8_t arr_b[N];
	uint32_t arr_src[4] = {1,1,1,1};

    for (int i=0; i<N; i++){
        arr_a[i] = 3;
        arr_b[i] = 5;
	}

    __m128i A,B,src,result;

	A = _mm_loadu_si128((__m128i*)&arr_a);
	print128_num_8(A);

	B = _mm_loadu_si128((__m128i*)&arr_b);
	print128_num_8(B);

	src = _mm_loadu_si128((__m128i*)&arr_src);
	print128_num_32(src);

	//result = _mm_add_epi16(A,B);
	//result = _mm_maddubs_epi16(A,B);
	result =  _mm_dpbusds_epi32(src,A,B);
	print128_num_32(result);

}

int main(int argc, char **argv){

    foo();

    return 0;
}
