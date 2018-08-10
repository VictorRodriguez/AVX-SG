#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


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

int check_result(){

    int ret = 0;
    for (int i=0; i<N; i++){
        if (arr_c[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            printf("%d\n",arr_c[i]);
            break;
    }
    return ret;
}

int main(int argc, char **argv){

    if (__builtin_cpu_supports ("avx512f")){
        // initialize arrays
        fill_arrays();
        foo();
        if (check_result())
            return -1;
        printf("Works!!\n");
        return 0;
    }
    else{
        printf("SKIP: instructions not supproted\n");
    }
}
