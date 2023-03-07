#include<stdio.h>
#include "mpi.h"
int main(int argc,char *argv[])
{
int iproc;
int MyRank,Numprocs,Root=0;
int value,sum=0;
int source,source_tag;
int Destination,Destination_tag;
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
if(MyRank==Root)
{
for(iproc=1;iproc<Numprocs;iproc++)
{
source=iproc;
source_tag=0;
MPI_Recv(&value,1,MPI_INT,source,source_tag,MPI_COMM_WORLD,&status);
sum=sum+value;
}
printf("MyRank = %d,SUM=%d\n",MyRank,sum);
}
else
{
Destination=0;
Destination_tag=0;
MPI_Send(&MyRank,1,MPI_INT,Destination,Destination_tag,MPI_COMM_WORLD);
}
MPI_Finalize();
}
