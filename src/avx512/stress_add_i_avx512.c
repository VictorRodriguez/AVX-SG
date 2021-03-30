#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"

#define BILLION 1E9

u_int32_t a[256] = {0};
u_int32_t b[256] = {0};
u_int32_t c[256] = {0};

int N = 256;

void foo(){
    __m512i m_a, m_b, m_c;
    for(int i = 0; i < sizeof(a)/sizeof(a[0]); i+=NUM_32B_INT_IN_M512){
        m_a = _mm512_load_epi32(&a[i]);
        m_b = _mm512_load_epi32(&b[i]);

        m_c = _mm512_add_epi32(m_a, m_b);
        _mm512_store_epi32(&c[i], m_c);
    }
}

int main(int argc, char **argv){

	struct test_parameters param;
	param = parameters_handler(argc,argv);

    fill_array_int(&a[0],sizeof(a)/sizeof(a[0]),param.x_value);
    fill_array_int(&b[0],sizeof(b)/sizeof(b[0]),param.y_value);

    struct timespec start, stop;
    double accum;

    clock_gettime( CLOCK_REALTIME, &start);

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

    param.avg_time_taken =(accum) /param.loops;

    if (check_arrays_int(param.x_value + param.y_value,&c[0],
		sizeof(c)/sizeof(c[0])))
        return -1;
    print_result(param.loops,param.delay_value,accum,param.avg_time_taken,
            param.x_value,
            param.y_value,
            param.x_value + param.y_value);
    return 0;
}
