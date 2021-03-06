#include <iostream>
#include "mpi.h"


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

  int sizeG1 = (size-1)/2;// +size%2;
  int sizeG2 = (size-1)-sizeG1;// -sizeG1;

  int n = size*sizeG1*sizeG2;
  int n = 5;
  

  // std::cout << sizeG1  << " "<< sizeG2 << std::endl;

  int *ranksG1 = new int[sizeG1];
  int *ranksG2 = new int[sizeG1];

  for(int i=0; i<sizeG1; i++)
    {
      ranksG1[i] = i+1;
    }

  for(int i=0; i<sizeG2; i++)
    {
      ranksG2[i] = sizeG1+i+1;
    }

  

  int *rankMasters = new int[3];

  rankMasters[0] = 0;
  rankMasters[1] = 1;
  rankMasters[2] = sizeG1+1;

  // grupy
  MPI_Comm_group(MPI_COMM_WORLD, &global);
  MPI_Group_incl(global, sizeG1, ranksG1, &workG1);
  MPI_Group_incl(global, sizeG2, ranksG2, &workG2);
  MPI_Group_incl(global, 3, rankMasters, &mastersG);



  // komunikatory 
  MPI_Comm_create(MPI_COMM_WORLD, workG1, &COMM_workG1);
  MPI_Comm_create(MPI_COMM_WORLD, workG2, &COMM_workG2);
  MPI_Comm_create(MPI_COMM_WORLD, mastersG, &COMM_mastersG);
  int *tab =  new int[n];  
  if(rank == 0)
    {

      for(int i=0; i<n;i++)
	tab[i] = i*(-1*i%2)/(i+1);
    }
  if( rank == 0 || rank == 1 || rank == sizeG1+1 )
    {
      MPI_Bcast(tab, n, MPI_INT, 0, COMM_mastersG);
      MPI_Bcast(&n, 1, MPI_INT, 0, COMM_mastersG);
    }

  for(int i=0; i<sizeG1; i++)
    {
      if(rank == ranksG1[i])
	{
	  
	  MPI_Comm_rank(COMM_workG1, &rankL);
	  MPI_Comm_size(COMM_workG1, &sizeL);
	  int fragment = n/sizeL;
	  MPI_Bcast(&fragment, 1, MPI_INT, 0 ,COMM_workG1);
	  int *tabL = new int[fragment];

	  MPI_Scatter(tab, 1, MPI_INT, tabL, 1, MPI_INT, 0, COMM_workG1);
	  // MPI_Scatter(tab, n, MPI_INT, tabL, fragment, MPI_INT, 0, COMM_workG1); 
	  MPI_Reduce(&tab, &maxL, 1, MPI_INT, MPI_MAX, 0, COMM_workG1);

	}
    }



  for(int i=0; i<sizeG2; i++)
    {
      if(rank == ranksG2[i])
	{
	  
	  MPI_Comm_rank(COMM_workG2, &rankL);
	  MPI_Comm_size(COMM_workG2, &sizeL);
	  int fragment = n/sizeL;
	  MPI_Bcast(&fragment, 1, MPI_INT, 0 ,COMM_workG2);
	  int *tabL = new int[fragment];

	  MPI_Scatter(tab, 1, MPI_INT, tabL, 1, MPI_INT, 0, COMM_workG2);
	  // MPI_Scatter(tab, n, MPI_INT, tabL, fragment, MPI_INT, 0, COMM_workG1); 
	  MPI_Reduce(&tab, &minL, 1, MPI_INT, MPI_MIN, 0, COMM_workG2);

	}
    }

  
  if(rank == 1)
    {
      MPI_Send(&maxL, 1, MPI_INT, 0, 0, COMM_mastersG);

    }
  if(rank == sizeG1+1)
    {
      MPI_Send(&minL, 1, MPI_INT, 0, 0, COMM_mastersG);

    }

  if (rank == 0)
    {
      MPI_Recv(&maxL, 1, MPI_INT, 1, 0, COMM_mastersG, &status);
      MPI_Recv(&minL, 1, MPI_INT, 2, 0, COMM_mastersG, &status);

      std::cout << "maxL: "  << maxL << " minL: " << minL << std::endl;
    }
  
  MPI_Finalize();
 
  return 0;
}
