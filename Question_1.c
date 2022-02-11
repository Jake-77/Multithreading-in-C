#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *runThread(void *param){

    for (int i = 0; i < 5; i++){

        printf("I am a Custom Thread Function Created By user\n");
        sleep(1);
    }

    pthread_exit(0);
}


int main(void){
    printf("This program would create threads\n");

    pthread_t tid;
    pthread_attr_t attr;

    //create thread
    int checkTID = pthread_create(&tid, NULL, runThread, NULL);
    
    if (checkTID == -1){
        printf("\nFAILED TO CREATE THREAD \n");
        exit(1);
    }else {

        sleep(1);
        printf("Custom Thread Created Successfully\n");
        int i = 0;
        for (i; i < 5; i++){
            printf("I am the process thread created by the compiler by default.\n");
            sleep(1);
        }

        //waits for thread to exit
        pthread_join(tid, NULL);

    }

	return 0;


}


/*
--------------------------------------------------------------------
ANSWER TO Q1:::
---------------------------------------------------------------------
Me and my partner do not see any ambiguity when running the code it prints 
as expected. 

*/ 