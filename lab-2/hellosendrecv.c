#include <stdio.h>
#include "mpi.h"

#define FROM_MASTER 1

int main(int argc, char *argv[]) {

    int rank, nprocs;
    char message[12] = "Hello, world";
    char ack[10] = "Received";
    
    /* status for MPI_Recv */
    MPI_Status status;
    
    /* Initialize MPI execution environment */
    MPI_Init(&argc, &argv);
    /* Determines the size of MPI_COMM_WORLD */
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    /* Give each process a unique rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
    /* If the process is the master */
    if ( rank == 0 )
    {
        /* Send message to process whose rank is 1 in the MPI_COMM_WORLD */
        MPI_Send(&message, 12, MPI_CHAR, 1, FROM_MASTER, MPI_COMM_WORLD);
        MPI_Recv(&ack, 12, MPI_CHAR, 1, FROM_MASTER, MPI_COMM_WORLD, &status);
        //MPI_Recv(&ack, 12, MPI_CHAR, 1, FROM_MASTER, MPI_COMM_WORLD);
        printf("Process %d says : %s\n", rank, ack); 
    }
    /* If the process has rank of 1 */
    else if ( rank == 1 ) {
        /* Receive message sent from master */
        MPI_Recv(&message, 12, MPI_CHAR, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        /* Print the rank and message */
        printf("Process %d says : %s\n", rank, message); 
        MPI_Send(&ack, 12, MPI_CHAR, 0, FROM_MASTER, MPI_COMM_WORLD);
    }
    
    /* Terminate MPI execution environment */
    MPI_Finalize();
}
