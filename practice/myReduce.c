#include "mpi.h"
#include <stdio.h>
#include  <stdlib.h>

int dataSize = 100;
float data[100];


int main(int argc, char *argv[]){

    int numTasks, taskId;

    float result = 0;

    for(int i=0; i < dataSize; i++){
        data[i] = (i+1) * 1.0;
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    
    int num_elements_per_process = (dataSize/(numTasks-1));
    float rcv_buffer[dataSize];

    MPI_Scatter(&data, dataSize, MPI_FLOAT, &rcv_buffer, num_elements_per_process, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float sum = 0;
    int begin = taskId*(dataSize/numTasks),end = begin+10;

    for(int i=begin; i<end; i++){
        sum += rcv_buffer[i];
    }

    printf("Rank %d sum = %f\n", taskId, sum);

    MPI_Reduce(&sum, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (taskId == 0){
        printf("Gathered\n");

        printf( "Final sum = %f\n", result);
    }

    MPI_Finalize();

}