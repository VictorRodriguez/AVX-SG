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

float floats[N] = {123.123};

void foo(float a, float b){

	float arr_a[4] = {a};
	float arr_b[4] = {b};

	printf("a array = %.6f\n",arr_a[0]);
	printf("b array = %.6f\n",arr_b[0]);
	printf("floats array = %.6f\n",floats[0]);

	A = _mm_loadu_ps(&arr_a[0]);
	B = _mm_loadu_ps(&arr_b[0]);

	result =  _mm_cvtneps_pbh(A);
	_mm_store_ps(&floats[0],result);

	printf("floats array after = %.6f\n",floats[0]);
	printf("floats array after = %.6f\n",floats[1]);
	printf("floats array after = %.6f\n",floats[2]);
	printf("floats array after = %.6f\n",floats[3]);
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
