#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>

float a[256] = {0};
float b[256] = {0};
float c[256] = {0};

void foo(){
	for (int i=0; i<256; i++){
		a[i] = a[i] + b[i];
	}
}

void fill_arrays(){
    for (int i=0; i<256; i++){
        b[i] = 1.0;
        c[i] = 2.0;

    }
}

int check_arrays(){
    int ret = 0;
    for (int i=0; i<256; i++){
        if (a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            break;
    }
    return ret;
}
int main(int argc, char **argv){

    fill_arrays();
    foo();
    if (check_arrays())
        return -1;
    printf("Works !!!\n");
    return 0;
}

