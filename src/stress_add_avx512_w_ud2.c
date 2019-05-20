#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


#define LOOPS 1000000000000

float a[256] = {0};
float b[256] = {0};
float c[256] = {0};

void fill_arrays_floats(float *b, float *c,
        float random_1, float random_2){
    for (int i=0; i<256; i++){
        b[i] = random_1;
        c[i] = random_2;
    }
}


void foo(){
    __m512 result,B,C;
        for (int i=0; i<256; i+=16){
            B =  _mm512_load_ps(&b[i]);
            C =  _mm512_load_ps(&c[i]);
            result = _mm512_add_ps(B,C);
            _mm512_store_ps(&a[i], result);
        }
}

int main(int argc, char **argv){

    float x_value = 1000 * (float)rand()/RAND_MAX;
    float y_value = 1000 * (float)rand()/RAND_MAX;

    // initialize arrays
    fill_arrays_floats(&b[0],&c[0],x_value,y_value);

    //do operation
    for (int x=0; x<LOOPS; x++){
        foo();
    }
}
