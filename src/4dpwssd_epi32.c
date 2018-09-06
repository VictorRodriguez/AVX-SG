/*
 * AVX-512 Vector Neural Network Instructions Word variable precision (4VNNIW)
 * - vector instructions for deep learning, enhanced word, variable precision.
 *   for Knights Mill (Xeon Phi x205) processors (2017)
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>


u_int32_t *arr_a, *arr_b, *arr_c, *arr_d,*arr_result;
int N = 256;

void fill_arrays(){
    arr_a = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_b = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_c = _mm_malloc(sizeof(u_int32_t) * N, 64);
    arr_d = _mm_malloc(sizeof(u_int32_t) * N, 64);

    for(int i = 0; i < N; i++) {
        arr_a[i] = 1;
        arr_b[i] = 2;
        arr_c[i] = 1;
        arr_d[i] = 2;
    }
}

void foo(){

    __m512i m_a, m_b, m_c, m_d,src,result;
    __m128i values = _mm_setr_epi32(0x1234, 0x2345, 0x3456, 0x4567);
    for( int i = 0; i < N; i+=16){
        m_a = _mm512_load_epi32(&arr_a[i]);
        m_b = _mm512_load_epi32(&arr_b[i]);
        m_c = _mm512_load_epi32(&arr_a[i]);
        m_d = _mm512_load_epi32(&arr_b[i]);

        result = _mm512_4dpwssd_epi32(src,m_a,m_b,m_c,m_d,&values);
        _mm512_store_epi32(&arr_result[i], result);
        printf("%d\n",arr_result[i]);

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
