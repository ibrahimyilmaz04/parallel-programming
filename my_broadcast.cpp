#include <mpi.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include<iomanip>
# define Master 0

using namespace std;


void my_broadcast (void* rec ,int count, MPI_Datatype type , int root , MPI_Comm comm);
  

int main (int argc , char** argv)
{
	int rank ;
	double sender [100000], mpi_broadcast_time, my_broadcast_time;
        clock_t start , stop;
	MPI_Init (NULL, NULL);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	
	for (int i =0 ; i<100000; i++)
	{
		sender [i]=i;
	}
	

	double mpi_start,mpi_end,my_start,my_end;
   
   MPI_Barrier (MPI_COMM_WORLD);
	mpi_start = MPI_Wtime();
   
   MPI_Bcast(&sender , 100000 , MPI_INT, Master , MPI_COMM_WORLD);
   MPI_Barrier (MPI_COMM_WORLD);
	mpi_end = MPI_Wtime();
    



   MPI_Barrier (MPI_COMM_WORLD);
	my_start = MPI_Wtime();
   
   my_broadcast (&sender , 100000 , MPI_INT, Master , MPI_COMM_WORLD);
   MPI_Barrier (MPI_COMM_WORLD);
	my_end = MPI_Wtime();
    
   if (rank == Master)
   {
	cout<<std::setprecision(10);
	cout<<std::fixed;
	cout<<MPI_Wtime()<<endl;
   	cout<<" MPI_broadcast_time ="<<mpi_end-mpi_start<<"\n";
   	cout<<" MY_broadcast_time ="<<my_end-my_start<<"\n";
   }
   MPI_Finalize();
   return 0;
}
void my_broadcast (void* rec ,int count, MPI_Datatype type , int root , MPI_Comm comm)	
   {
   	int rank , size ;
   	MPI_Comm_rank (comm , &rank);
   	MPI_Comm_size (comm, &size);
   	if (rank == Master)
   	{
   		for (int i=1; i< size ; i++) 
    	{
		   
   	    	MPI_Send (rec, count,type, i ,Master,comm);
   	    }
	}
	else 
	{
		MPI_Recv (rec , count, type , root, Master, comm, MPI_STATUS_IGNORE);
	}
   }


 