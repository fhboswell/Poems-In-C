//
//  main.c
//  Gradient_Descent
//
//  Created by Henry Boswell on 8/6/17.
//  Copyright © 2017 Henry Boswell. All rights reserved.
// Inspired by Andrew Ng's course on machine learning



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFF 65536

char buffer [BUFF];

void printMAT(double *MAT,int N){
    
    printf("N = %d \n", N);
    for (int i = 0; i <  4; i++){
        printf("\n");
        for (int j = 0; j < 4; j++){
            printf(" %f ",*(MAT + i*N + j));
            
        }
    }
}
void printVec(double *MAT,int N){
    
    printf("N = %d \n", N);
    for (int i = 0; i <  N; i++){
       
        printf(" %f ",*(MAT + i));
            
        
    }
}
int main(int argc, char *argv[])
{
    
    int N = 16384;
    int M = 256;
    
    double *X = (double *)calloc(N * M, sizeof(double));
    
    
    //int actual = 97;
    
    
    int i = 0;
    int j = 0;
    FILE *fp = fopen("dataset.csv", "r");
    if(fp != NULL){
        while(fgets(buffer, 800, (FILE*) fp)) {
            
            for (char *p = strtok(buffer,","); p != NULL; p = strtok(NULL, ","))
            {
                double f = (double)atof(p);
                
                //printf("token  : %s\n", p);
                *(X + i*N + j) = f;
                i++;
                //printf("i: %d", i);
                printf("j: %d", j);
            }
            i = 0;
            j++;
            
            
            
        }
    
        fclose(fp);
    }
    double *Y = (double *)calloc(M, sizeof(double));
    
    
    //int actual = 97;
    
    
    i = 0;
    j = 0;
    FILE *fpy = fopen("datasety.csv", "r");
    if(fpy != NULL){
        while(fgets(buffer, 800, (FILE*) fpy)) {
            
            for (char *p = strtok(buffer,","); p != NULL; p = strtok(NULL, ","))
            {
                double f = (double)atof(p);
                
                //printf("token  : %s\n", p);
                *(Y + i) = f;
                i++;
                //printf("i: %d", i);
                //printf("j: %d", j);
            }
            
            
            
            
        }
        fclose(fpy);

    
        
         printMAT(X,N);
        printVec(Y,M);
        //normalize(X, N, 3);
        /*
        normalize(yVEC, N, 1);
        printMAT(X,N);
        printMAT(yVEC ,N);
        printf("here");
        computeCost(X, yVEC, Theta,N);
        //void gradient_descent(long double* X, long double* y, long double*theta, int alpha, int epoch, int N, int params){
        Theta = gradient_descent(X,yVEC,Theta,0.001,10000,N,3);
        //naive_IKJ_Square(X,XT,inner, N);
        printMAT(X,N);
        printMAT(yVEC ,N);
        //printMAT(theta ,N);
        
        long double test =  (*(Theta))*(*(X+N))+(*(Theta+1))*(*(X+1+N))+(*(Theta+2))*(*(X+2+N));
        printf("\n %Lf \n", test);
        printf("\n %Lf \n", (*(yVEC + N)));
        
        //printf("%d",j);
        //printMAT(inner,N);
         */
        
    }
}

