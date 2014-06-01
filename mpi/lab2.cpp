#include <iostream>
#include "mpi.h"




float max(const double &a, const double &b)
{
  return (a>b)?a:b;
}




int main(int argc, char *argv[])
{



  int reszta, rank, size, msg;
  int n,nrank;

  MPI_Status status;



  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // std::cout << "Podaj n: ";
  // std::cin >> n;
  
  // int nSize = n/size;
  // reszta = n%size;

  int nRank[size];
  
  double *tab, *t;




  if(rank == 0)
    {

      std::cout << "Podaj n: ";
      std::cin >> n;
  
      tab = new double[n];


      for (int i = 0; i<n; i++)
	{
	  tab[i] = 1.0*i/size+1.0*size/(i+1);
	}

      for(int i=0; i<size; i++)
	{
	  nRank[i] = n/size;

	  if(i<n%size)
	    {
	      nRank[i]++;
	    }
	}

    }

  MPI_Scatter(nRank,1,MPI_INT, &nrank, 1, MPI_INT, 0, MPI_COMM_WORLD);

  t = new double[nrank];

  if(rank == 0)
    {
      for(int i=1; i<size; i++)
	MPI_Send(tab+nRank[i-1], nRank[i], MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      t = tab;
    }
  else
    {
      MPI_Recv(t, nrank, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    }


  double mx = t[0];
  double maxAll;

  
  for(int i=1; i<nrank;i++)
    {

      mx = max(mx, t[i]);

    }
  std::cout << "Dla rank: " << rank << " mx wynosi: " << mx << std::endl;

  MPI_Reduce(&mx, &maxAll, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  if(rank == 0)
    std::cout << "MPI_REDUCE" << rank << ": " << maxAll << std::endl;
  




 
  MPI_Finalize();
  delete t, tab; 
  return 0;
}
