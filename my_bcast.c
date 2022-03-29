#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>

void my_bcast(void* data, int count, MPI_Datatype datatype, int root,
              MPI_Comm communicator) {
  int world_rank;
  MPI_Comm_rank(communicator, &world_rank);
  int world_size;
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) {
    // If we are the root process, send our data to everyone
    int i;
    for (i = 0; i < world_size; i++) {
      if (i != world_rank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
      }
    }
  } else {
    // If we are a receiver process, receive the data from the root
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}

int main(int argc, char** argv) {
  
  

  MPI_Init(NULL, NULL);
   //int nthreads = atoi(argv[1]);

  int world_rank;
  double k[100000];
  int nthreads;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  double total_my_bcast_time = 0.0;
  double total_mpi_bcast_time = 0.0;
  for (int i =0; i<100000; i++)
		{
         		k[i]=i*2;
                        
         	}

  

   
    // Time my_bcast
    // Synchronize before starting timing
    MPI_Barrier(MPI_COMM_WORLD);
    total_my_bcast_time -= MPI_Wtime();
    my_bcast(&k, 100000, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // Synchronize again before obtaining final time
    MPI_Barrier(MPI_COMM_WORLD);
    total_my_bcast_time += MPI_Wtime();

    // Time MPI_Bcast
    MPI_Barrier(MPI_COMM_WORLD);
    total_mpi_bcast_time -= MPI_Wtime();
    MPI_Bcast(&k, 100000, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    total_mpi_bcast_time += MPI_Wtime();
  

  // Print off timing information
  if (world_rank == 0) {
    printf(" my_bcast time = %lf\n", total_my_bcast_time);
    printf(" MPI_Bcast time = %lf\n", total_mpi_bcast_time);
    
  }

  
  MPI_Finalize();
}
