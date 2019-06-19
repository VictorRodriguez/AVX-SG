#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include <pthread.h>

// slow loop
//#define LOOPS 1000000000000

// fast loop
#define LOOPS 1000000
#define THREADS 48

float a_256[256] = {0};
float a_512[256] = {0};
float b[256] = {0};
float c[256] = {0};


void fill_arrays_floats(float random_1, float random_2){
    for (int i=0; i<256; i++){
        b[i] = random_1;
        c[i] = random_2;
    }
/*
    for (int i=0; i<256; i++){
        printf("b = %f\n",b[i]);
        printf("c = %f\n",c[i]);
    }
*/

}

void foo_256(){
    __m256 result,B,C;
        for (int i=0; i<256; i+=8){
            B =  _mm256_load_ps(&b[i]);
            C =  _mm256_load_ps(&c[i]);
            result = _mm256_add_ps(B,C);
            _mm256_store_ps(&a_256[i], result);
        }
}

//void foo_512(){
//
//    //do operation
//	__m512 result,B,C;
//        for (int i=0; i<256; i+=16){
//            B =  _mm512_load_ps(&b[i]);
//            C =  _mm512_load_ps(&c[i]);
//            result = _mm512_add_ps(B,C);
//            _mm512_store_ps(&a_512[i], result);
//        }
//
//}

void *ThreadFoo(void *vargp) {
    for (int x=0; x<LOOPS; x++){
        foo_256();
        //foo_512();
    }
}

int main(int argc, char **argv){

    float x_value = 1000 * (float)rand()/RAND_MAX;
    float y_value = 1000 * (float)rand()/RAND_MAX;

    float result = x_value + y_value;

    // initialize arrays
    fill_arrays_floats(x_value,y_value);

    printf("Expected result = %f\n" , result);
    pthread_t tid[THREADS];
    for (int i = 0; i < THREADS; i++){
        pthread_create(&(tid[i]), NULL, ThreadFoo,NULL);
	}

    for (int i = 0; i < THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    for (int i=0; i<256; i++){
        if (a_256[i] != result){
            printf("Error in element %d\n",i);
            return -1;
        }
    }
    printf("Test PASS\n");

}

