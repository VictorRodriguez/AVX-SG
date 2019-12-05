#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"

#define BILLION 1E9
#define MAXRAND 100
#define N 256

int32_t arr_a[N] = {0};
int32_t arr_b[N] = {0};
int32_t arr_c[N] = {0};
int32_t result[N];

void foo(){
// Multiplies the individual unsigned bytes of the first source operand by the
// corresponding signed bytes of the second source operand, producing
// intermediate signed word results. The word results are then summed and
// accumulated in the destination dword element size operand.
// This instruction supports memory fault suppression.

    __m128i A,B,C,values;
    for( int i = 0; i < N; i+=4){
        A = _mm_load_si128((__m128i*)&arr_a[i]);
        B = _mm_load_si128((__m128i*)&arr_b[i]);
        C = _mm_load_si128((__m128i*)&arr_c[i]);
        values = _mm_dpbusd_epi32(C,B,A);
        _mm_store_si128((__m128i*)&result[i],values);
        /*
        printf("A = %d\n",A[0]);
        printf("B = %d\n",B[0]);
        printf("C = %d\n",C[0]);
        printf("values = %d\n",values[0]);
        printf("pre result = %d\n",result[0]);
        */
    }

    // alternative way to do this with fixed values
    // __m128i values = _mm_setr_epi32(0x0003, 0x0003, 0x0003, 0x0003);
    // values = _mm_dpbusd_epi32(values, values, values);
    // printf("%d\n",values[1]);
}

int main(int argc, char **argv){

    double avg_time_taken;
    int delay_value = 0; // in useconds
    long int loops = 10000000000;

    srand((unsigned)time(NULL));
    int x_value = (rand() % MAXRAND) + 1;
    int y_value = (rand() % MAXRAND) + 1;
    int z_value = (rand() % MAXRAND) + 1;


	struct test_parameters param;
	param = parameters_handler(argc,argv);

    fill_arrays_floats(&b[0],&c[0],param.x_value,param.y_value);

    printf("x = %d\n",x_value);
    printf("y = %d\n",y_value);
    printf("z = %d\n",z_value);

    for (int i=0; i<N; i++){
        arr_a[i] = (int32_t)x_value;
        arr_b[i] = (int32_t)y_value;
        arr_c[i] = (int32_t)z_value;
    }

    struct timespec start, stop;
    double accum;
    clock_gettime( CLOCK_REALTIME, &start);

    for (int x=0; x<loops; x++){
        foo();
        if (delay_value){
            usleep(delay_value);
        }
    }
    clock_gettime( CLOCK_REALTIME, &stop);

    accum = ( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;
    
    avg_time_taken =(accum)/loops;

    int expected_res = ((x_value*y_value) + z_value);
    printf("expect result = %d\n",expected_res);
    printf("result = %d\n",result[0]);
    if (check_arrays_int(expected_res,&result[0],N))
        return -1;
    print_result_vnni(loops,delay_value,accum,avg_time_taken,
            x_value,
            y_value,
            z_value,
            expected_res);
    return 0;
}
