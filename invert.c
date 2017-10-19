//
//  main.c
//  Gradient_Descent
//
//  Created by Henry Boswell on 8/6/17.
//  Copyright © 2017 Henry Boswell. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//  main.c
//  invert
//
//  Created by Henry Boswell on 8/6/17.
//  Copyright © 2017 Henry Boswell. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void gluInvertMatrix4X4(const long double m[16], long double * C);
void strassen_invert(long double *MATA, long double*MATC, int N);



void printMAT(long double *MAT,int N){
    
    printf("N = %d \n", N);
    for (int i = 0; i <  N; i++){
        printf("\n");
        for (int j = 0; j < 10; j++){
            printf(" %LG",*(MAT + i*N + j));
            
        }
    }
}
void reshape(long double *MATAA, long double *MATBB, int N){
    for (int i = 0; i <  N; i++){
        for (int j = 0; j < N; j++){
            *(MATBB + i*N + j) = *(MATAA + i*N*2 + j);
            //printf(" %d ",*(MATAA + i*N*2 + j));
        }
    }
}

void reshape_neg(long double *MATAA, long double *MATBB, int N){
    for (int i = 0; i <  N; i++){
        for (int j = 0; j < N; j++){
            *(MATBB + i*N*2 + j) = -*(MATAA + i*N + j);
            //printf(" %d ",*(MATAA + i*N*2 + j));
        }
    }
}
void naive_IKJ_Square(long double *MAT1, long double *MAT2, long double*MAT4, int N){
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // MAT3[i][j] += MAT1[i][k] * MAT2[k][j];
                *(MAT4 + i*N + j) += *(MAT1 + i*N + k) * *(MAT2 + k*N + j);
            }
        }
    }
    
    
}
void naive_IKJ_Square_sub_out(long double *MAT1, long double *MAT2, long double*MAT4, int N){
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // MAT3[i][j] += MAT1[i][k] * MAT2[k][j];
                *(MAT4 + i*N*2 + j) += *(MAT1 + i*N + k) * *(MAT2 + k*N + j);
            }
        }
    }
    
    
}
void naive_IKJ_Square_sub_second(long double *MAT1, long double *MAT2, long double*MAT4, int N){
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // MAT3[i][j] += MAT1[i][k] * MAT2[k][j];
                *(MAT4 + i*N + j) += *(MAT1 + i*N + k) * *(MAT2 + k*N*2 + j);
            }
        }
    }
    
    
}
void subtraction(long double *MAT1, long double *MAT2, long double*MAT, int N){
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // MAT3[i][j] += MAT1[i][k] * MAT2[k][j];
            *(MAT + i*N + j) = *(MAT1 + i*N + j) - *(MAT2 + i*N + j);
        }
        
    }
}

void addition_SUB_MAT_OUT(long double *MAT1, long double *MAT2, long double*MAT, int N){
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // MAT3[i][j] += MAT1[i][k] * MAT2[k][j];
            *(MAT + i*N*2 + j) = *(MAT1 + i*N + j) + *(MAT2 + i*N + j);
        }
        
    }
}

#define BUFF 65536

char buffer [BUFF];
/*
 void printMAT(long double *MAT,int N){
 
 printf("N = %d \n", N);
 for (int i = 0; i <  N; i++){
 printf("\n");
 for (int j = 0; j < 24; j++){
 printf(" %f ",*(MAT + i*N + j));
 
 }
 }
 }
 */
void vector_transpose(long double*MAT4, int N){
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            
            *(MAT4 + i) += *(MAT4 + i*N + j);
            if(i != 0 || j != 0){
                *(MAT4 + i*N + j) = 0;
            }
            
        }
    }
    
    
    
}




int main(int argc, char *argv[])
{
    
    int N = 128;
    long double *X = (long double *)calloc(N * N, sizeof(long double));
    long double *XT = (long double *)calloc(N * N, sizeof(long double));
    long double *yVEC = (long double *)calloc(N * N, sizeof(long double));
    long double *inner = (long double *)calloc(N * N, sizeof(long double));
    long double *invert = (long double *)calloc(N * N, sizeof(long double));
    long double *final = (long double *)calloc(N * N, sizeof(long double));
    long double *final2 = (long double *)calloc(N * N, sizeof(long double));
    
    int i = 0;
    int j = 0;
    FILE *fp = fopen("in", "r");
    if(fp != NULL){
        while(fgets(buffer, 300, (FILE*) fp)) {
            
            printf("%s\n", buffer);
            i = 0;
            
            
            *(XT + i*N + j) = 1;
            *(X + j*N + i) = 1;
            
            
            
            int counter = 1;
            for (char *p = strtok(buffer,","); p != NULL; p = strtok(NULL, ","))
            {
                if(counter == 1 || counter == 11){
                    if(counter == 11){
                        long double f;
                        f = (long double)atof(p);
                        *(yVEC + j*N) = f;
                    }
                    
                }else{
                    long double f;
                    f = atof(p);
                    *(XT + i*N + j) = f;
                    *(X + j*N + i) = f;
                    
                    printf("token: %s\n", p);
                    
                }
                i++;
                counter++;
                
            }
            j++;
            
            
            
        }
        printMAT(XT,N);
        //printMAT(yVEC ,N);
        printf("here");
        fclose(fp);
        
        naive_IKJ_Square(X,XT,inner, N);
        
        //int j = determinantOfMatrix(inner, N);
        //printf("%d",j);
        
        printMAT(inner,N);
        strassen_invert(inner, invert, N);
        printMAT(invert,N);
        naive_IKJ_Square(invert,XT,final, N);
        printMAT(final,N);
        //vector_transpose(yVEC, N);
        naive_IKJ_Square(final,yVEC,final2, N);
        printMAT(final2,N);
        
        
    }
}

void strassen_invert(long double *MATA, long double*MATC, int N){
    
    if(N <= 4){
        printMAT(MATA, N);
        gluInvertMatrix4X4(MATA, MATC);
        return;
    }
    
    
    
    
    long double *A11 = (MATA + 0*N + 0);
    long double *A12 = (MATA + 0*N + ((N/2)));
    long double *A21 = (MATA + N*((N/2)) + 0);
    long double *A22 =  (MATA + N*((N/2))+((N/2)));
    
    long double *C11 = (MATC + 0*N + 0);
    long double *C12 = (MATC + 0*N + ((N/2)));
    long double *C21 = (MATC + N*((N/2)) + 0);
    long double *C22 =  (MATC + N*((N/2))+((N/2)));
    
    
    
    N = N/2;
    
    long double *S1 = (long double *)calloc(N * N, sizeof(long double));
    
    long double *A11A = (long double *)calloc(N * N, sizeof(long double));
    reshape(A11, A11A, N);
    strassen_invert(A11A, S1, N);
    
    
    
    long double *S2 = (long double *)calloc(N * N, sizeof(long double));
    long double *S3 = (long double *)calloc(N * N, sizeof(long double));
    
    long double *A21A = (long double *)calloc(N * N, sizeof(long double));
    reshape(A21, A21A, N);
    naive_IKJ_Square(S1, A21A, S2, N);
    
    //printf("here");
    //printMAT(S1, N);
    
    long double *A12A = (long double *)calloc(N * N, sizeof(long double));
    reshape(A12, A12A, N);
    naive_IKJ_Square( A12A, S1, S3, N);
    
    long double *S4 = (long double *)calloc(N * N, sizeof(long double));
    naive_IKJ_Square( A21A, S3, S4, N);
    
    long double *S5 = (long double *)calloc(N * N, sizeof(long double));
    long double *A22A = (long double *)calloc(N * N,sizeof(long double));
    reshape(A22, A22A, N);
    subtraction(S4, A22A, S5, N);
    printf("here");
    //printMAT(S4, N);
    
    long double *S6 = (long double *)calloc(N * N, sizeof(long double));
    strassen_invert(S5, S6, N);
    
    
    naive_IKJ_Square_sub_out(S3,S6, C12, N);
    naive_IKJ_Square_sub_out(S6,S2, C21, N);
    
    long double *S7 = (long double *)calloc(N * N, sizeof(long double));
    
    naive_IKJ_Square_sub_second(S3, C21, S7, N);
    
    
    addition_SUB_MAT_OUT(S1, S7, C11, N);
    reshape_neg(S6, C22, N);
    
    
    
}


void gluInvertMatrix4X4(const long double m[16], long double * C){//https://www.mesa3d.org slightly modified
    
    long double inv[16], det;
    int i;
    
    
    
    inv[0] = m[5]  * m[10] * m[15] -
    m[5]  * m[11] * m[14] -
    m[9]  * m[6]  * m[15] +
    m[9]  * m[7]  * m[14] +
    m[13] * m[6]  * m[11] -
    m[13] * m[7]  * m[10];
    
    
    
    inv[4] = -m[4]  * m[10] * m[15] +
    m[4]  * m[11] * m[14] +
    m[8]  * m[6]  * m[15] -
    m[8]  * m[7]  * m[14] -
    m[12] * m[6]  * m[11] +
    m[12] * m[7]  * m[10];
    
    inv[8] = m[4]  * m[9] * m[15] -
    m[4]  * m[11] * m[13] -
    m[8]  * m[5] * m[15] +
    m[8]  * m[7] * m[13] +
    m[12] * m[5] * m[11] -
    m[12] * m[7] * m[9];
    
    inv[12] = -m[4]  * m[9] * m[14] +
    m[4]  * m[10] * m[13] +
    m[8]  * m[5] * m[14] -
    m[8]  * m[6] * m[13] -
    m[12] * m[5] * m[10] +
    m[12] * m[6] * m[9];
    
    inv[1] = -m[1]  * m[10] * m[15] +
    m[1]  * m[11] * m[14] +
    m[9]  * m[2] * m[15] -
    m[9]  * m[3] * m[14] -
    m[13] * m[2] * m[11] +
    m[13] * m[3] * m[10];
    
    inv[5] = m[0]  * m[10] * m[15] -
    m[0]  * m[11] * m[14] -
    m[8]  * m[2] * m[15] +
    m[8]  * m[3] * m[14] +
    m[12] * m[2] * m[11] -
    m[12] * m[3] * m[10];
    
    inv[9] = -m[0]  * m[9] * m[15] +
    m[0]  * m[11] * m[13] +
    m[8]  * m[1] * m[15] -
    m[8]  * m[3] * m[13] -
    m[12] * m[1] * m[11] +
    m[12] * m[3] * m[9];
    
    inv[13] = m[0]  * m[9] * m[14] -
    m[0]  * m[10] * m[13] -
    m[8]  * m[1] * m[14] +
    m[8]  * m[2] * m[13] +
    m[12] * m[1] * m[10] -
    m[12] * m[2] * m[9];
    
    inv[2] = m[1]  * m[6] * m[15] -
    m[1]  * m[7] * m[14] -
    m[5]  * m[2] * m[15] +
    m[5]  * m[3] * m[14] +
    m[13] * m[2] * m[7] -
    m[13] * m[3] * m[6];
    
    inv[6] = -m[0]  * m[6] * m[15] +
    m[0]  * m[7] * m[14] +
    m[4]  * m[2] * m[15] -
    m[4]  * m[3] * m[14] -
    m[12] * m[2] * m[7] +
    m[12] * m[3] * m[6];
    
    inv[10] = m[0]  * m[5] * m[15] -
    m[0]  * m[7] * m[13] -
    m[4]  * m[1] * m[15] +
    m[4]  * m[3] * m[13] +
    m[12] * m[1] * m[7] -
    m[12] * m[3] * m[5];
    
    inv[14] = -m[0]  * m[5] * m[14] +
    m[0]  * m[6] * m[13] +
    m[4]  * m[1] * m[14] -
    m[4]  * m[2] * m[13] -
    m[12] * m[1] * m[6] +
    m[12] * m[2] * m[5];
    
    inv[3] = -m[1] * m[6] * m[11] +
    m[1] * m[7] * m[10] +
    m[5] * m[2] * m[11] -
    m[5] * m[3] * m[10] -
    m[9] * m[2] * m[7] +
    m[9] * m[3] * m[6];
    
    inv[7] = m[0] * m[6] * m[11] -
    m[0] * m[7] * m[10] -
    m[4] * m[2] * m[11] +
    m[4] * m[3] * m[10] +
    m[8] * m[2] * m[7] -
    m[8] * m[3] * m[6];
    
    inv[11] = -m[0] * m[5] * m[11] +
    m[0] * m[7] * m[9] +
    m[4] * m[1] * m[11] -
    m[4] * m[3] * m[9] -
    m[8] * m[1] * m[7] +
    m[8] * m[3] * m[5];
    
    inv[15] = m[0] * m[5] * m[10] -
    m[0] * m[6] * m[9] -
    m[4] * m[1] * m[10] +
    m[4] * m[2] * m[9] +
    m[8] * m[1] * m[6] -
    m[8] * m[2] * m[5];
    
    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if(det == 0){
        for (i = 0; i < 16; i++){
            *(C + i) = 0;
            //printf("%f", inv[i] * det);
        }
        
    }else{
        det = 1.0 / (det);
        
        // printf("%f", det);
        
        for (i = 0; i < 16; i++){
            *(C + i) = inv[i] * det;
            //printf("%f", inv[i] * det);
        }
        
    }
    
    
    
}

