// Proces 0 wyznacza tablice lp
// Proces 0 rozsyla tablice lp
// Kazdy proces posiada tablice t={1.1.1...p}
// Kazdy proces wykresla wielokrotnosci kolejnej wartosci z tabli
  // MPII_REDUCE robi 'AND' na tablicy

#include <iostream>
#include "mpi.h"
#include <math.h>

int main(int argc, char *argv[])
{

  int rank, size, lp[5], p;

  //ranksP - parzyste
  //ranksN - nieparzystey

  MPI_Status status;

  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  
  
  
  if(rank == 0)
    {
      // p = 144;
      std::cin >> p;
      lp[0] = 2;
      lp[1] = 3;
      lp[2] = 5;
      lp[3] = 7;
      lp[4] = 11;
      // MPI_Scatter(lp, 1, MPI_INT, &rank, 1, MPI_INT, 0, MPI_COMM_WORLD);
      // MPI_Bcast(lp, 5, MPI_INT, 0, MPI_COMM_WORLD);

    }

  MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(lp, 5, MPI_INT, 0, MPI_COMM_WORLD);

  int *tab = new int[p];
  
  for(int i=0;i<p;i++)
    {

      tab[i]=1;
    }

  
  for(int i=2; i<p; i++)
    {
      if( (lp[rank]*i) < p)
  	tab[lp[rank]*i] = 0;
    }
  
  tab[0]  = 0;
  tab[1]  = 0;
  int *t1 = new int[p];

  MPI_Reduce(tab, t1, p, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);

  if(rank == 0)
    {
      for(int i=0; i<p; i++)
  	std::cout << i << ": "  << t1[i] << std::endl;
    }
  
  MPI_Finalize();
  delete t1, tab;
  return 0;
}
