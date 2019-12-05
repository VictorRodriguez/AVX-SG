#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"

#define BILLION 1E9

float a[256] = {0};
float b[256] = {0};
float c[256] = {0};

void foo(){
    __m256 result,B,C;
        for (int i=0; i<256; i+=sizeof(__m256)/sizeof(float)){
            B =  _mm256_load_ps(&b[i]);
            C =  _mm256_load_ps(&c[i]);
            result = _mm256_add_ps(B,C);
            _mm256_store_ps(&a[i], result);
        }
}
int main(int argc, char **argv){

	struct test_parameters param;
	param = parameters_handler(argc,argv);

    fill_array_float(&b[0],sizeof(b)/sizeof(b[0]),param.x_value);
    fill_array_float(&c[0],sizeof(c)/sizeof(c[0]),param.y_value);

    struct timespec start, stop;
    double accum;

    clock_gettime(CLOCK_REALTIME, &start);

    for (int x=0; x<param.loops; x++){
        foo();
        if (param.delay_value){
            usleep(param.delay_value);
        }
    }

    clock_gettime( CLOCK_REALTIME, &stop);

    accum = ( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;

    param.avg_time_taken =(accum)/param.loops;

    if (check_arrays_float(param.x_value + param.y_value,&a[0]))
        return -1;
    print_result(param.loops,param.delay_value,accum,param.avg_time_taken,
            param.x_value,
            param.y_value,
            param.x_value + param.y_value);
    return 0;
}
