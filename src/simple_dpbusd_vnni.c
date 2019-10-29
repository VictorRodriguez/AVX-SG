#include <stdio.h>
#include <immintrin.h>
#include <time.h>
#include <stdint.h>

#define MAXRAND 100
#define N 8

//int32_t result[N];


void print128_num(__m128i var)
{
    uint16_t *val = (uint16_t*) &var;
    printf("Numerical: %i %i %i %i %i %i %i %i \n",
           val[0], val[1], val[2], val[3], val[4], val[5],
           val[6], val[7]);
}

void foo(){

	uint16_t arr_a[N];
	uint16_t arr_b[N];

    for (int i=0; i<N; i++){
        arr_a[i] = 2;
        arr_b[i] = 3;
    }

    __m128i A,B,result;

	A = _mm_loadu_si128((__m128i*)&arr_a);
	print128_num(A);

	B = _mm_loadu_si128((__m128i*)&arr_b);
	print128_num(B);

	result = _mm_add_epi32(A,B);
	print128_num(result);

}

int main(int argc, char **argv){


//    int x_value = (rand() % MAXRAND) + 1;
//    int y_value = (rand() % MAXRAND) + 1;
//    int z_value = (rand() % MAXRAND) + 1;

//    int x_value = 0;
//    int y_value = 1;
//    int z_value = 0;

//    int expected_res = 0;
//	expected_res = ((x_value*y_value) + z_value);

//    printf("x = %d\n",x_value);
//    printf("y = %d\n",y_value);
//    printf("z = %d\n",z_value);


    foo();

//    for (int i=0; i<N; i++){
//		printf("%d ",result[i]);
//		if(result[i] != expected_res){
//			printf("Arithmetic Error\n");
//			return -1;
//		}
//	}
//	printf("VPDPBUSD works correctly!\n");
//	printf("Result: %d\n",expected_res);

    return 0;
}
