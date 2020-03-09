/*
* References:
https://www.anandtech.com/show/14179/intel-manual-updates-bfloat16-for-cooper-lake-xeon-scalable-only

https://software.intel.com/sites/default/files/managed/c5/15/architecture-instruction-set-extensions-programming-reference.pdf

*/

#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdint.h>
#include "common.h"

#define MAXRAND 10
#define N 4

__m128 A,B,result;

float result_array[N] = {123.123};

void print128_num(__m128 var, char* variable){
    float *val = (float*) &var;
    printf("%s: %f %f %f %f \n",variable,
           val[0], val[1], val[2], val[3]);
}

void print128_num_fp16(__m128 var, char* variable){
    __fp16 *val = (__fp16*) &var;
    printf("%s: %f %f %f %f \n",variable,
           (__fp16)val[0], (__fp16)val[1],(__fp16)val[2],(__fp16)val[3]);
}

void foo(float a, float b){

	float arr_a[4] = {a};
	float arr_b[4] = {b};

	printf("a array = %.6f\n",arr_a[0]);
	printf("b array = %.6f\n",arr_b[0]);
	printf("result array = %.6f\n",result_array[0]);

	A = _mm_loadu_ps(&arr_a[0]);
	print128_num(A,"A");

	B = _mm_loadu_ps(&arr_b[0]);
	print128_num(B,"B");

	/* __m128bh _mm_cvtneps_pbh (__m128 a)
	Convert packed single-precision (32-bit) floating-point elements in a to
	packed BF16 (16-bit) floating-point elements, and store the results in dst. 
	*/
	result = _mm_cvtneps_pbh(A);
	print128_num_fp16(result,"result _mm_cvtneps_pbh(A)");

	/* __m128bh _mm_cvtne2ps_pbh (__m128 a, __m128 b)
	Convert packed single-precision (32-bit) floating-point elements in two
	vectors a and b to packed BF16 (16-bit) floating-point elements, and store
	the	results in single vector dst. */
	result = _mm_cvtne2ps_pbh(A,B);
	print128_num_fp16(result,"result _mm_cvtne2ps_pbh(A,B)");

	/* __m128 _mm_dpbf16_ps (__m128 src, __m128bh a, __m128bh b)
	Compute dot-product of BF16 (16-bit) floating-point pairs in a and b,
	accumulating the intermediate single-precision (32-bit) floating-point
	elements with elements in src, and store the results in dst.
	*/
	result = _mm_dpbf16_ps(A,A,B);
	print128_num_fp16(result,"result _mm_dpbf16_ps(A,A,B)");

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
