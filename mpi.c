#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]) 

{
	int number = atoi(argv[1]);
	char *str = argv[2];
	
	
	MPI_Init(NULL, NULL);
	int rank , size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	number = number -1;
	if (rank != 0)
	{	  
		MPI_Recv (&number , 1, MPI_INT, rank-1, 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
		MPI_Recv (str , 100, MPI_CHAR, rank-1, 0 , MPI_COMM_WORLD,MPI_STATUS_IGNORE );
		printf ("process = %d receiving message = %s and number = %d  to process= %d\n", rank, str, number , rank -1 ); 
		char buffer [33];
    		sprintf(buffer,"%d",rank);
                strcat(str, buffer); 
	}
	number = number +1;
	MPI_Send (&number, 1 , MPI_INT, (rank+1)%size,    0,  MPI_COMM_WORLD);  
    	MPI_Send (str, strlen(str)+1 , MPI_CHAR, (rank+1)%size, 0, MPI_COMM_WORLD );

    	if(rank ==0)
	{ 
		MPI_Recv (&number , 1, MPI_INT, size-1, 0 , MPI_COMM_WORLD ,MPI_STATUS_IGNORE);       
		MPI_Recv (str , 100, MPI_CHAR, size-1, 0 , MPI_COMM_WORLD,MPI_STATUS_IGNORE );
		printf ("process = %d receiving message = %s and number = %d  to process= %d\n", rank, str, number , size -1);
	}

	
    	
        
	
	MPI_Finalize();
    	return 0;
	
}