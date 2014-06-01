#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{

  int rank, size, msg;
  MPI_Status status;
  int *tab;
  int *t;
  t = new int[3];
  tab = new int[size*3];


  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);


  if(rank==0)
    {
    for(int i=0; i<size*3;i++)
      tab[i] = i;
  
    MPI_Send(&tab[3], 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&tab[6], 3, MPI_INT, 2, 0, MPI_COMM_WORLD);
    MPI_Send(&tab[9], 3, MPI_INT, 3, 0, MPI_COMM_WORLD);

    
    }
  else
    {
      MPI_Recv(t, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      for(int i=0; i<3; i++)
	t[i] = tab[i];
      cout << rank << " " << t[0] << endl;
    }


  // eksperyment

    // MPI_Send(tab+3*rank, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
    // MPI_Send(tab[6], 3, MPI_INT, 2, 0, MPI_COMM_WORLD);
    // MPI_Send(tab[9], 3, MPI_INT, 3, 0, MPI_COMM_WORLD);



  // if(rank == 0)
  //   {
  //     msg = 2;
  //     MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

      
  //     MPI_Recv(&msg, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
  //     cout << msg;
  //   }
  // else
  //   {
  //     MPI_Recv(&msg, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
  //     if(rank%2 == 0)
  // 	    {
  // 	      msg = msg*rank;
  // 	    }
  // 	  else
  // 	    msg = msg+rank;

  //     if(rank<size-1)
  // 	{

  // 	  MPI_Send(&msg, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
  // 	}
  //     else
  // 	  MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);	

  // }

  //   if(rank<size-1)

  // 	}
  // }      
      

  // cout << rank << " = " << msg << endl;



  
  // else if(rank == 2)
  //   {
  //     MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
  //     msg = msg + rank; // 1 + 2 = 3
  //     MPI_Send(&msg, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);  
  //   }
  // else if (rank == 3)
  //   {
  //     MPI_Recv(&msg, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
  //     msg = msg + rank; // 3 + 3 = 6
  //     cout << "Jeden proces " << rank << " z " << size << " procesow\n" << "msg: " << msg;
  //   }




  // pokolei
  //   else if(rank == 2)
  //   {
  //     MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
  //     msg = msg + rank; // 1 + 2 = 3
  //     MPI_Send(&msg, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);  
  //   }
  // else if (rank == 3)
  //   {
  //     MPI_Recv(&msg, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
  //     msg = msg + rank; // 3 + 3 = 6
  //     cout << "Jeden proces " << rank << " z " << size << " procesow\n" << "msg: " << msg;
  //   }


      
      
  // MPI_Send(*msg, count, datatype, tag, comm);
  // MPI_Recv(*msg, count, datatype, source, tag, comm, *status);

  MPI_Finalize();
  return 0;
}
