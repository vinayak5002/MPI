#include "mpi.h"
#include <stdio.h>
#include  <stdlib.h>

int main(int argc, char *argv[]){

    int numTasks, taskId;
    int dataSize = 10;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);
    
    int num_elements_per_process = (dataSize/(numTasks-1));
    float data[dataSize], rcv_buffer[num_elements_per_process];

    float results[numTasks-1];

    for(int i=0; i < dataSize; i++){
        data[i] = (i+1) * 1.0;
    }

    MPI_Scatter(&data, num_elements_per_process, MPI_FLOAT, &rcv_buffer, num_elements_per_process, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float sum = 0;

    for(int i=0; i<num_elements_per_process; i++){
        sum += rcv_buffer[i];
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gather(&sum, 1, MPI_FLOAT, &results, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if (taskId == 0){
        printf("Gathered\n");
        float total = 0;

        for(int i=0; i<numTasks-1; i++){
            total += results[i];
        }

        printf( "Final sum = %f\n", total);
    }

    MPI_Finalize();

}