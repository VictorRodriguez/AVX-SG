#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"

#define BILLION 1E9
#define N 256

int32_t arr_a[N];
int32_t arr_b[N];
int32_t arr_c[N];
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
        values = _mm_dpbusd_epi32(A,B,C);
        _mm_store_si128((__m128i*)&result[i],values);
    }

    // alternative way to do this with fixed values
    // __m128i values = _mm_setr_epi32(0x0003, 0x0003, 0x0003, 0x0003);
    // values = _mm_dpbusd_epi32(values, values, values);
    // printf("%d\n",values[1]);
}

int main(int argc, char **argv){

    double avg_time_taken;
    double time_taken;
    int delay_value = 0; // in useconds
    long int loops = 10000000000;

    srand((unsigned)time(NULL));
    float x_value = 1000 * (float)rand()/RAND_MAX;
    float y_value = 1000 * (float)rand()/RAND_MAX;
    float z_value = 1000 * (float)rand()/RAND_MAX;

    int key;
    while ((key = getopt (argc, argv, "hd:l:x:y:")) != -1)
    switch (key){
      case 'h':
        print_help();
        return 0;
      case 'd':
        delay_value = atoi(optarg);
        break;
      case 'l':
        loops = atoi(optarg);
        break;
      case 'x':
        x_value = atof(optarg);
        break;
      case 'y':
        y_value = atof(optarg);
        break;
      case '?':
        if (optopt == 'd' || optopt == 'l')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return -1;
    }


    fill_arrays_integers(&arr_a[0],N,(int)x_value);
    fill_arrays_integers(&arr_b[0],N,(int)y_value);
    fill_arrays_integers(&arr_c[0],N,(int)z_value);

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

    int expected_res = (x_value*y_value) + z_value;
    if (check_arrays_int(expected_res,&result[0],N))
        return -1;
    print_result(loops,delay_value,accum,avg_time_taken,
            x_value,
            y_value,
            x_value+y_value);
    return 0;
}
