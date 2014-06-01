#include <iostream>
#include "mpi.h"

using namespace std;


int main(int argc, char *argv[])
{

  int rank, size, rankL, sizeL, maxL, minL;

  //ranksP - parzyste
  //ranksN - nieparzyste
  MPI_Status status;
  MPI_Group global,workG2, workG1, mastersG;
  MPI_Comm COMM_workG1, COMM_workG2, COMM_mastersG;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);



  double a = 10;
  int i=0;
  while(true)
    {
      i++;
      a += 10.0*i/(1.0*rank+1.0);
      if(i%10==0) MPI_Bcast(&a, 1, MPI_DOUBLE, i%size, MPI_COMM1_WORLD);
      cout << rank << " " << a <<  endl;
    }

			  
  return 0;
}
