#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>

#define BILLION 1E9

u_int32_t *arr_a, *arr_b, *arr_c;
int N = 256;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_b = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_c = _mm_malloc(sizeof(u_int32_t) * N, 64);
    for(int i = 0; i < N; i++) {
        arr_a[i] = 1;
        arr_b[i] = 2;
    }
}

void foo(){

    __m512i m_a, m_b, m_c;

    for( int i = 0; i < N; i+=16){
        m_a = _mm512_load_epi32(&arr_a[i]);
        m_b = _mm512_load_epi32(&arr_b[i]);

        m_c = _mm512_add_epi32(m_a, m_b);
        _mm512_store_epi32(&arr_c[i], m_c);
    }
}

int check_arrays(){
    int ret = 0;
    for (int i=0; i<256; i++){
        if (arr_a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            break;
    }
    return ret;
}
void print_help(){
    printf("-h : Help\n");
    printf("-d <delay> : Delay in useconds\n");
    printf("-l <delay> : Loops\n");
}

int main(int argc, char **argv){

    clock_t t;
    double avg_time_taken;
    double time_taken;

    // initialize arrays
    fill_arrays();

    int delay_value = 0; // in useconds
    long int loops = 10000000000;
    int index;
    int c;

    opterr = 0;
    while ((c = getopt (argc, argv, "hd:l:")) != -1)
    switch (c){
      case 'h':
        print_help();
        return 0;
      case 'd':
        delay_value = atoi(optarg);
        break;
      case 'l':
        loops = atoi(optarg);
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
    
    avg_time_taken =(accum) /loops;

    if (check_arrays())
        return -1;


    printf("Loops: %d\n",loops);
    printf("Delay per function: %.9g in seconds \n",(delay_value/1E6));
    printf("Total time: %.9g seconds to execute \n",accum);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken );
    return 0;
}
