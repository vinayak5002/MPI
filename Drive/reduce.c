
/*
 * Copyright (c) 2004-2006 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2006      Cisco Systems, Inc.  All rights reserved.
 *
 * Sample MPI "hello world" application in C
 */

#include <stdio.h>
#include "mpi.h"
#define SIZE 12
int main(int argc, char* argv[])
{
    int rank=0, size, sendcount=4, recvcount = 4 ;
    float var=0,globalvar;

    float sendbuf[SIZE] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 , 9.0, 10.0, 11.0, 12.0 };
    float recvbuf[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    

    MPI_Scatter(sendbuf,sendcount,MPI_FLOAT,recvbuf,recvcount,MPI_FLOAT,0,MPI_COMM_WORLD);

    for(int i=0;i<12;i++)
	printf(" %d %f ",rank,recvbuf[i]);
   
    for(int i=0;i<recvcount; i++)
	var = var + recvbuf[i];

    MPI_Reduce(&var,&globalvar,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    
    printf("Process %d Exists with var : %f\n",rank,var);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    if(rank==0)printf("\n Global var is %f ",globalvar);
    return 0;
}
