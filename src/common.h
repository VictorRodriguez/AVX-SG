#include <stdint.h>

#define NUM_8B_INT_IN_M128  (sizeof(__m128i)/sizeof(uint8_t))
#define NUM_16B_INT_IN_M128 (sizeof(__m128i)/sizeof(uint16_t))
#define NUM_32B_INT_IN_M128 (sizeof(__m128i)/sizeof(uint32_t))

#define NUM_8B_INT_IN_M256  (sizeof(__m256i)/sizeof(uint8_t))
#define NUM_16B_INT_IN_M256 (sizeof(__m256i)/sizeof(uint16_t))
#define NUM_32B_INT_IN_M256 (sizeof(__m256i)/sizeof(uint32_t))

void fill_array_uint8_t_128(uint8_t *array,uint8_t value){
    for (int i=0; i<NUM_8B_INT_IN_M128; i++){
        array[i] = (uint8_t)value;
	}
}


void fill_array_uint16_t_256(uint16_t *array,uint16_t value){
    for (int i=0; i<NUM_16B_INT_IN_M256; i++){
        array[i] = (uint16_t)value;
	}
}

void print128_num_32(__m128i var) {
    uint32_t *val = (uint32_t*) &var;
	for(int i = 0; i < NUM_32B_INT_IN_M128; i++)
		printf("%u ",val[1]);
	printf("\n");
}
void print128_num_16(__m128i var){
    uint16_t *val = (uint16_t*) &var;
	for(int i = 0; i < NUM_16B_INT_IN_M128; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void print128_num_8(__m128i var){
    uint8_t *val = (uint8_t*) &var;
	for(int i = 0; i < NUM_8B_INT_IN_M128; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void print256_num_32(__m256i var) {
    uint32_t *val = (uint32_t*) &var;
	for(int i = 0; i < NUM_32B_INT_IN_M256; i++)
		printf("%u ",val[1]);
	printf("\n");
}
void print256_num_16(__m256i var){
    uint16_t *val = (uint16_t*) &var;
	for(int i = 0; i < NUM_16B_INT_IN_M256; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void print256_num_8(__m256i var){
    uint8_t *val = (uint8_t*) &var;
	for(int i = 0; i < NUM_8B_INT_IN_M256; i++)
		printf("%i ",val[1]);
	printf("\n");
}

void print_result(long int loops,
        int delay_value,
        double accum,
        double avg_time_taken,
        float operator_1,
        float operator_2,
        float result){

    printf("PASS: Benchmark completed\n");
    printf("Loops: %ld\n",loops);
    printf("Delay per function: %.9g in seconds \n",(delay_value/1E6));
    printf("Total time: %.9g seconds to execute \n",accum);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken );
    printf("Operator1: %f\n",operator_1);
    printf("Operator2: %f\n",operator_2);
    printf("Result: %f\n",result);
}

void print_result_vnni(long int loops,
        int delay_value,
        double accum,
        double avg_time_taken,
        float operator_1,
        float operator_2,
        float operator_3,
        float result){

    printf("PASS: Benchmark completed\n");
    printf("Loops: %ld\n",loops);
    printf("Delay per function: %.9g in seconds \n",(delay_value/1E6));
    printf("Total time: %.9g seconds to execute \n",accum);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken );
    printf("Operator1: %f\n",operator_1);
    printf("Operator2: %f\n",operator_2);
    printf("Operator3: %f\n",operator_3);
    printf("Result: %f\n",result);
}

void print_help(){
    printf("-h : Help\n");
    printf("-d <delay> : Delay in useconds\n");
    printf("-l <loops> : Loops\n");
    printf("-x <value> : floating value\n");
    printf("-y <value> : floating value\n");
}

void fill_arrays_floats(float *b, float *c,
        float random_1, float random_2){
    for (int i=0; i<256; i++){
        b[i] = random_1;
        c[i] = random_2;
    }
}

int check_arrays_int(int result, int32_t *a, int N){
    int ret = 0;
    for (int i=0; i<N; i++){
        if (a[i] == result)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            break;
    }
    return ret;
}

int check_arrays_float(float result, float *a){
    int ret = 0;
    for (int i=0; i<256; i++){
        if (a[i] == result)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            break;
    }
    return ret;
}

