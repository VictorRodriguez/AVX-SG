/*
* References:
https://www.anandtech.com/show/14179/
	intel-manual-updates-bfloat16-for-cooper-lake-xeon-scalable-only

https://software.intel.com/sites/default/files/managed/c5/15/
	architecture-instruction-set-extensions-programming-reference.pdf

*/

#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdint.h>
#include "common.h"

#define MAXRAND 10
#define N 4

__m512 A,B,result;
__m256bh result_bfl16;

float result_array[N] = {123.123};
/*
void print512_num(__m512 var, char* variable){
    float *val = (float*) &var;
    printf("%s: %f %f %f %f \n",variable,
           val[0], val[1], val[2], val[3]);
}
*/

// This fuction was created by Ryan, Mark D
// Thanks Mark !!
/*
void print128_num_fp16bh(__m128bh var, char* variable){
	uint8_t ar[16];
    _mm_storeu_ps(ar, (__m128)result_bfl16);
    uint16_t *bfloats = (uint16_t*) &ar[0];
	printf("%s:\n",variable);
    for (size_t i = 0; i < 4; i++) {
            uint32_t tmp = ((uint32_t)bfloats[i]) << 16;
            float* ftmp_ptr = (float *)&tmp;
            printf("%f\n", *ftmp_ptr);
    }
}

void print128_num_fp16(__m128 var, char* variable){
	uint8_t ar[16];
    _mm_storeu_ps(ar, result);
    uint16_t *bfloats = (uint16_t*) &ar[0];
	printf("%s:\n",variable);
    for (size_t i = 0; i < 4; i++) {
            uint32_t tmp = ((uint32_t)bfloats[i]) << 16;
            float* ftmp_ptr = (float *)&tmp;
            printf("%f\n", *ftmp_ptr);
    }
}
*/

void foo(float a, float b){

	float arr_a[4] = {a};
	float arr_b[4] = {b};

	printf("a array = %.6f\n",arr_a[0]);
	printf("b array = %.6f\n",arr_b[0]);
	printf("result array = %.6f\n",result_array[0]);

	//A = _mm512_load_ps(&arr_a[0]);
	//print512_num(A,"A");

	//B = _mm_loadu_ps(&arr_b[0]);
	//print128_num(B,"B");

	/* __m128bh _mm_cvtneps_pbh (__m128 a)
	Convert packed single-precision (32-bit) floating-point elements in a to
	packed BF16 (16-bit) floating-point elements, and store the results in dst.
	*/
	result_bfl16 = _mm512_cvtneps_pbh(A);
	//print128_num_fp16bh(result_bfl16,"result _mm_cvtneps_pbh(A)");

	/* __m128bh _mm_cvtne2ps_pbh (__m128 a, __m128 b)
	Convert packed single-precision (32-bit) floating-point elements in two
	vectors a and b to packed BF16 (16-bit) floating-point elements, and store
	the	results in single vector dst. */
	//result_bfl16 = _mm_cvtne2ps_pbh(A,B);
	//print128_num_fp16bh(result_bfl16,"result _mm_cvtne2ps_pbh(A,B)");

	/* __m128 _mm_dpbf16_ps (__m128 src, __m128bh a, __m128bh b)
	Compute dot-product of BF16 (16-bit) floating-point pairs in a and b,
	accumulating the intermediate single-precision (32-bit) floating-point
	elements with elements in src, and store the results in dst.
	*/
	//result = _mm_dpbf16_ps(A, (__m128bh )A, (__m128bh) B);
	//print128_num_fp16(result,"result _mm_dpbf16_ps(A,A,B)");

	//TODO investigate how to print bfloat16 number
	//_mm_store_ps1(&result_array[0],result);
}

int main(int argc, char **argv){

	srand((unsigned)time(NULL));
	float a =  (rand() % MAXRAND) + 1;
	float b =  (rand() % MAXRAND) + 1;

	printf("a = %.6f\n", a);
	printf("b = %.6f\n", b);

    foo(a,b);

    return 0;
}
