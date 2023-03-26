#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 152987283
#define MASTER 0

float data[ARRAYSIZE];

int main(int argc, char *argv[]){

    int numTasks, taskId;

    for(int i=0; i < ARRAYSIZE; i++){
        data[i] = (i+1) * 1.0;
    }

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskId);

    if ( taskId == MASTER ){
        float total = 0, sum;
        
        for (int slave = 1; slave<numTasks; slave++){
            MPI_Recv(&sum, 1, MPI_FLOAT, slave, 5002, MPI_COMM_WORLD, &status);
            printf("Sum from %d: = %f\n", slave, sum);
            total += sum;
        }
        printf("Total Sum = %f\n", total);
    }
    else{
        float mySum = 0;
        int i;

        for(i=taskId-1; i<ARRAYSIZE; i+= (numTasks-1)){
            mySum += data[i];
        }
        printf("Last: %f\n", data[i-(numTasks-1)]);

        MPI_Send(&mySum, 1, MPI_FLOAT, MASTER, 5002, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}