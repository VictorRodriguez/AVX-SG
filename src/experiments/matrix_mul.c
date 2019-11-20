#include <stdio.h>
#include <immintrin.h>
#include <ctype.h>
#define N 4

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
void multiply(float mat1[][N], float mat2[][N], float res[][N]) {
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < N; k++)
                res[i][j] += mat1[i][k]*mat2[k][j];
        }
    }
}

void multiply_w_fma(float mat1[][N], float mat2[][N], float res[][N]) {
    __m256 RESULT,A,B,C;
    int i, j, k;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j += sizeof(__m256)/sizeof(float))
        {
            res[i][j] = 0;
            C =  _mm256_load_ps(&res[i][j]);
            for (k = 0; k < N; k+=8)

                A =  _mm256_load_ps(&mat1[i][k]);
                B =  _mm256_load_ps(&mat1[k][j]);

                RESULT = _mm256_fmadd_ps(A,B,C);
        }
        _mm256_storeu_ps(&res[i][j],RESULT);
    }
}

int main(){
    float mat1[N][N] = { {1, 1, 1, 1},
                    {2, 2, 2, 2},
                    {3, 3, 3, 3},
                    {4, 4, 4, 4}};

    float mat2[N][N] = { {1, 1, 1, 1},
                    {2, 2, 2, 2},
                    {3, 3, 3, 3},
                    {4, 4, 4, 4}};

    float res[N][N];
    float res_w_fma[N][N];
    int i, j;

    multiply(mat1, mat2, res);
    multiply(mat1, mat2, res_w_fma);

    printf("\nResult matrix is \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
           printf("%.2f ", res[i][j]);
        printf("\n");
    }

    printf("\nResult matrix w/ fma is \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
           printf("%.2f ", res_w_fma[i][j]);
        printf("\n");
    }
    return 0;
}
