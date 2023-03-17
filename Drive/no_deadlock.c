#include <stdio.h>
#include "mpi.h"
/* process 0 send a number to and receive a number from process 1.
process 1 receive a number from and send a number to process 0
*/
int main(int argc, char** argv)
{ 
	/*** sample_safe1.c ****/
int my_rank, numbertoreceive, numbertosend ;
MPI_Request *requests;
MPI_Status status;
MPI_Init(&argc, &argv);

MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

if (my_rank==0){
numbertosend = 100;
MPI_Ssend( &numbertosend, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
MPI_Recv( &numbertoreceive, 1, MPI_INT, 1, 20, MPI_COMM_WORLD, &status);
printf("\n rank  %d %d ",my_rank,numbertoreceive);
}
else if(my_rank == 1)
{
numbertosend = 200;
MPI_Recv( &numbertoreceive, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
MPI_Ssend( &numbertosend, 1, MPI_INT, 0, 20, MPI_COMM_WORLD);
printf("\n rank  %d %d",my_rank,numbertoreceive);
}


MPI_Finalize();
return 0;
}
