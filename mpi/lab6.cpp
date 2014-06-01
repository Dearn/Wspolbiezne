// Proces 0 wyznacza tablice lp
// Proces 0 rozsyla tablice lp
// Kazdy proces posiada tablice t={1.1.1...p}
// Kazdy proces wykresla wielokrotnosci kolejnej wartosci z tabli
// MPII_REDUCE robi 'AND' na tablicy

#include <iostream>
#include "mpi.h"
#include <math.h>

int *znajdzpierwsze(int n) {
  int status = 1, num = 3, count, c;
  //prompting user to enter number of prime numbers to print


  int *tab = new int[n];
  // input is valid display first prime number
  if ( n >= 1 )
    {

      tab[0] = 2;
    }
 
  for ( count = 2 ; count <=n ;  ) //loop that will iterate through n numbers
    {
      for ( c = 2 ; c <= (int)sqrt(num) ; c++ )// for each element check whether it is prime or not
	{
	  //if numbe r is completely divisible by a number other than 1 and itselft,then number is not prime
	  if ( num%c == 0 ) 
	    {
	      status = 0;
	      break;
	    }
	}
      //if it is a prime number, print it
      if ( status != 0 )
	{
	  tab[count-1] = num;
	  count++;
	}
      status = 1;
      num++;
    
    }
  return tab;
}

int main(int argc, char *argv[])
{

  // int rank, size, lp[5], p;
  int rank, size, *lp, p;

  //ranksP - parzyste
  //ranksN - nieparzystey

  MPI_Status status;

  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  

  lp = new int[size];  
  
  
  if(rank == 0)
    {
      std::cin >> p;
      lp = znajdzpierwsze(size);

    }

  MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(lp, size, MPI_INT, 0, MPI_COMM_WORLD);

  int *tab = new int[p];
  // tab[0] = 0;
  // tab[1] = 0;
  
  for(int i=0;i<2;i++)
    {

      tab[i]=0;
    }
  
  for(int i=2;i<p;i++)
    {

      tab[i]=1;
    }


  for(int i=2; i<p; i++)
    {
      if( (lp[rank]*i) < p)
  	tab[lp[rank]*i] = 0;
    }


  int *t1 = new int[p];

  MPI_Reduce(tab, t1, p, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);


  if(rank == 0)
    {
      for(int i=0; i<p; i++)
  	if(t1[i] == 1)
  	  std::cout << i << " ";
      std::cout <<  std::endl;
      for(int i =0; i<p; i++)
	std::cout << i << ": " << t1[i] << "\t"; // << std::endl;
    }
  std::cout <<  std::endl;
  MPI_Finalize();
  delete t1, tab;
  return 0;
}
