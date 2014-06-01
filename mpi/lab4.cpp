#include <iostream>
#include "mpi.h"


int main(int argc, char *argv[])
{
  int sumAll;
  int rank, size, msg, rankL, sizeL;
  int sizeP;
  //ranksP - parzyste
  //ranksN - nieparzyste
  MPI_Status status;
  MPI_Group global, gp, gn;
  MPI_Comm cp, cn;

  int a = 0;
  if(rank == 0) a = 10;


  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);


  sizeP = size/2 + size%2;


  int ranksP[sizeP];


  for(int i=0; i<sizeP; i++)
    ranksP[i] = i*2;
      
  


  // Tworzenie grup
  MPI_Comm_group(MPI_COMM_WORLD, &global);  
  MPI_Group_incl(global, sizeP, ranksP, &gp);
  MPI_Group_difference(global, gp, &gn);

  // Tworzenie komunikatorow
  
  MPI_Comm_create(MPI_COMM_WORLD, gp, &cp);
  MPI_Comm_create(MPI_COMM_WORLD, gn, &cn);




  a = rank;
  if(rank%2 == 0)
    {
      MPI_Bcast(&a, 1, MPI_INT, 0, cp);
      MPI_Comm_rank(cp, &rankL);
      MPI_Comm_size(cp, &sizeL);
      MPI_Reduce(&rank, &sumAll, 1, MPI_DOUBLE, MPI_SUM, sizeL-1, cp);
      if(rankL == sizeL-1)
      	std::cout << sumAll << std::endl;
    }
  else
    {
      MPI_Bcast(&a, 1, MPI_INT, 0, cn);
       MPI_Comm_rank(cn, &rankL);
       MPI_Comm_size(cn, &sizeL);
       MPI_Reduce(&rank, &sumAll, 1, MPI_DOUBLE, MPI_SUM, sizeL-1, cn);
       if(rankL == sizeL-1)
       	 std::cout << sumAll << std::endl;
    }

  // std::cout << "rank " << rank  << " a= " << a << std::endl;
  // std::cout << "rank " << rank  << " rankL= " << rankL << std::endl;
  // std::cout << "rank " << rank  << " sizeL= " << sizeL << std::endl;
  std::cout << rank  << "| rankL = " << rankL << " sizeL = " << sizeL << " a= " << a << std::endl;



  // if(rankL == sizeL)
  //   std::cout << sumAll << std::endl;
  

  MPI_Finalize();  
  return 0;
}



