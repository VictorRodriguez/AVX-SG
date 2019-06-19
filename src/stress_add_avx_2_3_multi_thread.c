#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <immintrin.h>
#include <pthread.h>

// slow loop
//#define LOOPS 1000000000000

// fast loop
#define LOOPS 10000000
#define THREADS 48

float a_256[256] = {0};
float a_512[256] = {0};
float b[256] = {0};
float c[256] = {0};

void wrmsr_on_cpu(int cpu, int reg, u_int64_t v){

    int fd;
    char msr_file_name[64];
	sprintf(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = open(msr_file_name, O_WRONLY);
	if (fd < 0) {
        printf("Error opening file to write MSR");
	}

    int rc = pwrite(fd, &v, sizeof(v), reg);
    if (rc != sizeof(v)) {
        printf("Unable to write cpu:%d\n", cpu);
        printf("Register:%d\n",reg);
    }

	close(fd);
}

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

void foo_512(){

    //do operation
	__m512 result,B,C;
        for (int i=0; i<256; i+=16){
            B =  _mm512_load_ps(&b[i]);
            C =  _mm512_load_ps(&c[i]);
            result = _mm512_add_ps(B,C);
            _mm512_store_ps(&a_512[i], result);
        }

}

void *ThreadFoo(void *vargp) {
    for (int x=0; x<LOOPS; x++){
        foo_256();
        foo_512();
    }
}

void write_msr(){

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

    // if we want to capture on the scope, uncoment this lines
    sleep(5);
    int reg = 0x0;
    u_int64_t value = 0x0;
    wrmsr_on_cpu(0,reg,value);
    return 0;

    for (int i = 0; i < THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    for (int i=0; i<256; i++){
        if (a_256[i] != result){
            printf("Error in a_256, element %d\n",i);
            return -1;
        }
        //else {printf("a_256 pass\n");}

        if (a_512[i] != result){
            printf("Error in a_512, element %d\n",i);
            return -1;
        }
        //else{printf("a_512 pass\n");}
    }
    printf("Test PASS\n");

}

