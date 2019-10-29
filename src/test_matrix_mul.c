#include <ctype.h>
#include <stdio.h>
#include <immintrin.h>


float a[256];
float b[256];
float c[256];
float result[256];

void foo(){
    __m256 RESULT,A,B,C;
        for (int i=0; i<256; i+=8){

            A =  _mm256_load_ps(&a[i]);
            B =  _mm256_load_ps(&b[i]);
            C =  _mm256_load_ps(&c[i]);

            /* Performs a set of SIMD multiply-add computation on packed
             * single-precision floating-point values using three source
             * vectors/operands, a, b, and c. Corresponding values in two
             * operands, a and b, are multiplied and the infinite precision
             * intermediate results are added to corresponding values in the
             * third operand, after which the final results are rounded to the
             * nearest float32 values. */
            // RESULT = (A * B) + C
            RESULT = _mm256_fmadd_ps(A,B,C);

            _mm256_store_ps(&result[i], RESULT);
        }
}

void foo_simple(){
	for (int i=0; i<256; i+=8){
		result[i] = (a[i]*b[i]) + c[i];
	}

}

int main(){

    float a_value = 2.0;
    float b_value = 2.0;
    float c_value = 1.0;

    // result = 2 * 2 +1 = 5
    float expected_result = (a_value * b_value) + c_value;

    for ( int x = 0 ; x < 256 ; x++){
        a[x] = a_value;
        b[x] = b_value;
        c[x] = c_value;
    }

    foo();
    foo_simple();

    for ( int x = 0 ; x < 256 ; x++){
        if (result[x] != expected_result){
            printf("Error, arithemtic corrupted \n");
            printf("Position: %d",x);
            printf("result %f",result[x]);
            return -1;
        }
    }
    printf("Sanity test for _mm256_fmadd_ps PASS !\n");
    printf(" _mm256_fmadd_ps(%f,%f,%f) = %f\n"\
            ,a_value,b_value,c_value,expected_result);
    return 0;
}
