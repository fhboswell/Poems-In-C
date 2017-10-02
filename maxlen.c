

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maxlen( int* vec, int size){
    //setup
    int curr = *(vec);
    int len = 1;
    int maxlen = 0;
    //loop through vec
    for(int i = 1; i < size; i++){
        if(*(vec + i) == curr){
            len++;
        }else{
            //change the max
            if(maxlen < len){
                maxlen = len;
            }
            len = 1;
        }
        curr = *(vec + i);
    }
    return maxlen;
}

int main(int argc, char *argv[])
{
    
    int vec[] = {1,1,1,2,3,3,5,6,6,6,6,7,9};
    int size = 13;
    printf("\nMax Length: %d \n", maxlen(vec,size));
  
}

