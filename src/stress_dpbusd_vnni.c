#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>
#include "common.h"

#define BILLION 1E9

void foo(){
// Multiplies the individual unsigned bytes of the first source operand by the
// corresponding signed bytes of the second source operand, producing
// intermediate signed word results. The word results are then summed and
// accumulated in the destination dword element size operand.
// This instruction supports memory fault suppression.

    __m128i values = _mm_setr_epi32(0x0003, 0x0003, 0x0003, 0x0003);
    values = _mm_dpbusd_epi32(values, values, values);
    printf("%d\n",values[1]);
}

int main(int argc, char **argv){

    double avg_time_taken;
    double time_taken;
    int delay_value = 0; // in useconds
    long int loops = 10000000000;

    srand((unsigned)time(NULL));
    float x_value = 1000 * (float)rand()/RAND_MAX;
    float y_value = 1000 * (float)rand()/RAND_MAX;

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


    // initialize arrays
    //fill_arrays_floats(&b[0],&c[0],x_value,y_value);

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

    //if (check_arrays_float(x_value + y_value,&a[0]))
    //    return -1;
    //print_result(loops,delay_value,accum,avg_time_taken,
    //        x_value,
    //        y_value,
    //        x_value+y_value);
    return 0;
}
