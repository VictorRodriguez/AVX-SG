
void print_result(long int loops,
        int delay_value,
        double accum,
        double avg_time_taken){

    printf("PASS: Benchmark completed\n");
    printf("Loops: %d\n",loops);
    printf("Delay per function: %.9g in seconds \n",(delay_value/1E6));
    printf("Total time: %.9g seconds to execute \n",accum);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken );
}

void print_help(){
    printf("-h : Help\n");
    printf("-d <delay> : Delay in useconds\n");
    printf("-l <loops> : Loops\n");
}

void fill_arrays_floats(float *b ,float *c){
    for (int i=0; i<256; i++){
        b[i] = 1.0;
        c[i] = 2.0;
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

