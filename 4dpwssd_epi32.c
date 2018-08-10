#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <immintrin.h>

void foo(){

    int a[256] = {0}; 

    int b[256] = {0};
    int c[256] = {0};
    int d[256] = {0};
    int e[256] = {0};

    __m512i result,src,B,C,D,E;
    for (int i=0; i<256; i+=8){
        B =  _mm512_load_epi32(&b[i]);
        C =  _mm512_load_epi32(&c[i]);
        D =  _mm512_load_epi32(&d[i]);
        E =  _mm512_load_epi32(&e[i]);
        
        __m128i b = _mm_set_epi32(1,2,3,4);
        __m128i *ptrb = &b;
        result = _mm512_4dpwssd_epi32(src,B,C,D,E,ptrb);
        for ( int j=0;j<8;j++){
            a[i+j] = result[j];
        }
    }
}

int main(int argc, char **argv){
        foo();
}
