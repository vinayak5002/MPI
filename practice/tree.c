#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int scores[80];

int main( int argc, char *argv[] ){

    int numTasks, taskId;
    int arraySize = 80;

    for (int i=0; i<arraySize; i++){
        scores[i] = i+1;
    }

    int tasksRemaining = 8;
    int prcs [tasksRemaining];

    for(int i=0; i<tasksRemaining; i++){
        prcs[i] = i;
    }

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskId);

    int myMax = 0;
    int begin = taskId*(arraySize/numTasks),end = begin+10;

    for(int i=begin; i<end; i++){
        if(scores[i] > myMax){
            myMax = scores[i];
        }
    }

    while (tasksRemaining != 0 )
    {
        if(tasksRemaining == 1) break;

        for(int i=1; i<tasksRemaining; i++){
            if( i %2 == 0 ){
                int otherSum = 0;
                // printf("%d Reciving from %d\n", taskId,  prcs[i+1]);
                MPI_Recv(&otherSum, 1, MPI_INT, prcs[i+1], 1, MPI_COMM_WORLD, &status);
                if( otherSum > myMax ){
                    myMax = otherSum;
                }
            }
            else{
                // printf("%d Sending to %d\n", taskId, prcs[i-1]);
                MPI_Send(&myMax, 1, MPI_INT, prcs[i-1], 1, MPI_COMM_WORLD);
            }

        }
        int j=0, k=0;
        while(k<tasksRemaining){
            prcs[j] = prcs[k];
            j+=1; k+=2;
        } 
        tasksRemaining /= 2;
        for(int v=0; v<tasksRemaining; v++){
            printf("%d, ", prcs[v]);
        }
        printf("\n%d\n", tasksRemaining);
    }
    printf("processes %d reported maximum %d\n",taskId, myMax);
    
    if(taskId == 0){
        printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOORank 0's max = %d", myMax);
    }

    MPI_Finalize();
}