#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
// #define arraysize 1000000

int main(int argc,char **argv){
unsigned int size,rank,i,localsum,globalsum,tempsum;
localsum=0;
globalsum=0;
unsigned int arr[100000];
for(int i=0;i<100000;i++){
    arr[i]= i+1;
}

// arr = ;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
for(i=rank;i<100000;i+=size){
localsum=localsum+arr[i];
}
printf("localsum:%d\n",localsum);
if(rank==0){
for(i=1;i<size;i++){
MPI_Recv(&tempsum,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
globalsum=globalsum+tempsum;
}
}
else{
MPI_Send(&localsum,1,MPI_INT,0,0,MPI_COMM_WORLD);
}
if(rank==0){
printf("localsum=%d,globalsum=%d\n ",localsum,globalsum);
printf("finalsum=%d\n",globalsum+localsum);
}
MPI_Finalize();
}