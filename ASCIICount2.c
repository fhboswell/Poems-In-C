#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS 8
#define BUFF 65536



//Globals
int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* threads call this function */

char buffer [BUFF];
int letters[128];

struct threadData{
	int start;
	int end;
	pthread_t tid;
	int index;
};

int main(int argc, char *argv[])
{
	

	if (argc != 2) {
		fprintf(stderr,"usage: a.out <filename>\n");
		return -1;
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp != NULL){
		size_t newLen = fread(buffer, sizeof(char), BUFF, fp);
		if(ferror(fp) != 0){
			printf("error");
		}else {
			buffer[newLen++] = '\0';
		}
		fclose(fp);
	}


	//pthread_t tid[THREADS]; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */
/* get the default attributes */
	pthread_attr_init(&attr);

	struct threadData threadDataArray[THREADS];
	int partition = BUFF/THREADS;

	
	for(int i = 0; i < THREADS; i++){
		threadDataArray[i].index= i;
		//threadDataArray[i].tid = i;
		if(i == 0){
			threadDataArray[i].start = 0;
		}else{
			threadDataArray[i].start = (threadDataArray[i - 1].end) + 1;
		}
		threadDataArray[i].end = (i+1)*(BUFF/THREADS);
	}



	for (int j = 0; j < THREADS; j++)
   	{
      		pthread_create(&threadDataArray[j].tid, NULL, runner, &threadDataArray[j]);
        	
    	}
 	for (int k = 0; k < THREADS; k++)
    	{
      		if (pthread_join(threadDataArray[k].tid, NULL) != 0)
        	{
          		fprintf(stderr, "error: Cannot join thread # %d\n", k);
        	}
    	}	
	char temp = 0;
	for(int a = 1; a < 128; a++){
		int total = 0;
		total = letters[a];
		temp = a;
		//printf("%x", temp);
		printf("\n %d occurrences of ascii %c ",total, temp);


	}

	



	

}

/* The thread will begin control in this function */
void *runner(void *arg)
{
    struct threadData *data = arg;
	

	for (int i = data->start; i <= data->end; ++i){
		//printf("%x", buffer[i]);
		letters[buffer[i]-0] += 1;
        //printf("thread %d", data->index);
	}
    

	pthread_exit(0);
}
