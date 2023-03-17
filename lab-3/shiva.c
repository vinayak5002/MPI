#include <stdio.h>
#include<mpi.h>


int main(int argc, char *argv[]) {

    int rank, nprocs;
    
    
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
        printf("Enter a number\n");
        int number;
        scanf("%d",&number);
        MPI_Send(&number, 4, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&number, 4, MPI_INT, 2, 1, MPI_COMM_WORLD);
        
    }
    /* If the process has rank of 1 */
    else if ( rank == 1 ) {
        /* Receive message sent from master */
        int new;
        MPI_Recv(&new, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        /* Print the rank and message */
        for(int i=2;new/i<=i;i++){
            if(new%i == 0){
                printf("Rank 1 ,Not prime\n");
            }   
    	}
    	printf("Rank1 , prime\n");
    }
    else if (rank == 2) {
        int new1;
        MPI_Recv(&new1, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        if (new1 % 2 == 0){
            printf("Even number\n");
        }
        else {
            printf("Odd number\n");
        }
    }
    /* Terminate MPI execution environment */
    MPI_Finalize();
}


