#include <stdio.h>
#include <immintrin.h>
#include <time.h>

#define MAXRAND 100
#define N 256

int32_t arr_a[N] = {0};
int32_t arr_b[N] = {0};
int32_t arr_c[N] = {0};
int32_t result[N];

void foo(){
    __m128i A,B,C,values;
    for( int i = 0; i < N; i+=4){
        A = _mm_load_si128((__m128i*)&arr_a[i]);
        B = _mm_load_si128((__m128i*)&arr_b[i]);
        C = _mm_load_si128((__m128i*)&arr_c[i]);
        values = _mm_dpbusd_epi32(C,B,A);
        _mm_store_si128((__m128i*)&result[i],values);
    }
}

int main(int argc, char **argv){


    srand((unsigned)time(NULL));
    int x_value = (rand() % MAXRAND) + 1;
    int y_value = (rand() % MAXRAND) + 1;
    int z_value = (rand() % MAXRAND) + 1;

    int expected_res = 0;
	expected_res = ((x_value*y_value) + z_value);

    printf("x = %d\n",x_value);
    printf("y = %d\n",y_value);
    printf("z = %d\n",z_value);

    for (int i=0; i<N; i++){
        arr_a[i] = (int32_t)x_value;
        arr_b[i] = (int32_t)y_value;
        arr_c[i] = (int32_t)z_value;
    }

    foo();

    for (int i=0; i<N; i++){
		if(result[i] != expected_res){
			printf("Arithmetic Error\n");
			return -1;
		}
	}
	printf("VPDPBUSD works correctly!\n");
	printf("Result: %d\n",expected_res);

    return 0;
}
