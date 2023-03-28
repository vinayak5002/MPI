#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 1000
#define MASTER 0

float data[ARRAYSIZE];

int getPrev(int taskId, int numProcs){
    if (taskId == 0){
        return numProcs-1;
    }
    else{
        return taskId -1;
    }
}
int getNext(int taskId, int numProcs){
    return (taskId+1)%numProcs;
}

int main(int argc, char *argv[]){

    int numTasks, taskId;

    for(int i=0; i < ARRAYSIZE; i++){
        data[i] = (i+1) * 1.0;
    }

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskId);

    int nextProc = getNext(taskId, numTasks), prevProc = getPrev(taskId, numTasks);

    if( taskId == 0 ){
        float mySum = 0, totalSum = 0;

        for(int i=taskId-1; i<ARRAYSIZE; i+= (numTasks)){
            mySum += data[i];
        }

        MPI_Send(&mySum, 1, MPI_INT, nextProc, 1, MPI_COMM_WORLD);

        MPI_Recv(&totalSum, 1, MPI_FLOAT, prevProc, 1, MPI_COMM_WORLD, &status);

        printf("Rank 0 sum : %f\n", mySum);

        printf("Total Sum = %f\n", totalSum);
    }
    else{
        float otherSum;
        MPI_Recv(&otherSum, 1, MPI_FLOAT, prevProc, 1, MPI_COMM_WORLD, &status);
        
        float mySum = 0;
        int i;

        for(int i=taskId-1; i<ARRAYSIZE; i+= (numTasks)){
            mySum += data[i];
        }

        mySum += otherSum;

        MPI_Send(&mySum, 1, MPI_FLOAT, nextProc, 1, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
}