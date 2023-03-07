#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, nprocs;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if( rank == 0 ){
        int num;
        printf("Enter a number: ");
        scanf("%d", &num);

        MPI_Send(&num, 4, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&num, 4, MPI_INT, 2, 1, MPI_COMM_WORLD);
    }
    else if ( rank == 1 ){
        int OorE;
        MPI_Recv(&OorE, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        if( OorE%2 == 0 ){
            printf("Rank 1: Number %d is Even\n", OorE);
        }
        else{
            printf("Rank 1: Number %d is Odd\n", OorE);
        }
    }
    else if (rank == 2) {
        int n;
        MPI_Recv(&n, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        int prime = 1;
        for(int i=2; i<n/2; i++){
            if (n%i == 0){
                prime = 0;
                break;
            }
        }

        if(prime){
            printf("Rank 2: Number is prime");
        }
        else{
            printf("Rank 2: Number is not prime\n");
        }

    }

    MPI_Finalize();
}