#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>



MPI_Status status;
main(int argc, char **argv) {
   int N = atoi(argv[1]);
  double a[N][N],b[N][N];
  double c[N][N];
  int i,j,k,taskid,numtasks;
  
  struct timeval start, stop;
  
  gettimeofday(&start, 0);
  MPI_Init(&argc, &argv);
  
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  if (numtasks==1){
  
  for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
        a[i][j]= 1.0;
        b[i][j]= 2.0;
        c[i][j]= 0.0;
        
}
}

    for (i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            for(k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
            
        
		} 
		
    }
}
      gettimeofday(&stop, 0);
    fprintf(stdout,"Time = %.6f\n\n",
         (stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
         

  MPI_Finalize();
}
