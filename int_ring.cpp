#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size, N;
    // int value = 0; // if using integer
    int arrsize = 500000;
    int* value = new int[arrsize];
    double start_t, end_t;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        printf("error: not enough input");
        exit();
    }
    else{
        N = std::stoi(argv[1])
    }


    start_t = MPI_Wtime();

    for(int i = 0; i < N; i++) {
        if(rank == 0) {
            // Uncomment when using int
            // MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            // MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // value += rank; 

            // uncomment when using arr
            MPI_Send(&value, arrsize, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&value, arrsize, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } 
        else{
            // Uncomment when using int
            // MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // value += rank;
            // MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

            // uncomment when using arr
            MPI_Recv(&value, arrsize, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&value, arrsize, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            
        }
    }

    end_t = MPI_Wtime();

    if (rank == 0) {
        std::cout << "total value after " << N << " loops: " << value << std::endl;
        std::cout << "total time: " << end_t - start_t << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
