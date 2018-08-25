
void print_result(long int loops,
        int delay_value,
        double accum,
        double avg_time_taken,
        float operator_1,
        float operator_2,
        float result){

    printf("PASS: Benchmark completed\n");
    printf("Loops: %d\n",loops);
    printf("Delay per function: %.9g in seconds \n",(delay_value/1E6));
    printf("Total time: %.9g seconds to execute \n",accum);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken );
    printf("Operator1: %f\n",operator_1);
    printf("Operator2: %f\n",operator_2);
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

