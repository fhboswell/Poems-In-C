

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


float * y( float x1, float x2, float x3, float y1, float y2, float y3, float * out){
    //float out[3];
    float D = (x1 - x2)*(x1 - x3)*(x2 - x3);
    out[0]  = (x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2)) / D;
    out[1] = (pow(x3, 2) * (y1 - y2) + pow(x2, 2) * (y3 - y1) + pow(x1, 2) * (y2 - y3)) / D;
    out[2] = (x2 * x3 * (x2 - x3) * y1 + x3 * x1 * (x3 - x1) * y2 + x1 * x2 * (x1 - x2) * y3) / D;
    return out;
}

float lagrange(float * xVec, float * yVec, int size, float xpred){
     float yNaught =0;
    for(int i=0; i<size; i++)
    {
        //yNaught =0;
        float mod = yVec[i];
        for (int j=0; j < size;j++)
        {
            if (j != i){
                float D = (xVec[i] - xVec[j]);
                mod = mod * (xpred - xVec[j])/D;
            }
        }
        yNaught += mod;
    }
    return yNaught;
}

int main(int argc, char *argv[])
{
    float xVec[3],yVec[3];
    printf("\nEnter X and Y values \n");
    for(int i=0; i<3; i++)
    {
        scanf ("%f",&xVec[i]);
        scanf("%f",&yVec[i]);
    }
    printf("\n The table\n");
    for(int i = 0; i<3; i++)
    {
        printf("%0.2f\t%0.2f",xVec[i],yVec[i]);
        printf("\n");
    }
    float out[3];
     y(xVec[0],xVec[1],xVec[2],yVec[0],yVec[1],yVec[2], out);
    float inc = (xVec[2]- xVec[0])/40;
    printf("Algebraic\t\t Interpolation");
    for(float i = xVec[0]; i < xVec[2]; i = i + inc){
        float yNaught =  out[0] * (i * i) + out[1] * (i) + out[2];
         printf("\n%0.2f\t%0.2f",i, yNaught);
        printf("\t\t  %0.2f\t%0.2f",i, lagrange(xVec, yVec,3, i));
    }
}

