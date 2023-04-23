#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    int value = 0;
    double start_t, end_t;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc != 2) {
        printf("error: not enough input");
        exit(1);
    }
    else{
        N = std::stoi(argv[1]);
    }

    start_t = MPI_Wtime();

    for(int i = 0; i < N; i++) {
        if(rank == 0) {
            MPI_Send(value, array_size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(value, array_size, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            value += rank;
        } 
        else{
            MPI_Recv(value, array_size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            value += rank;
            MPI_Send(value, array_size, MPI_DOUBLE, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }
    }

    end_t = MPI_Wtime();

    if (rank == 0) {
        std::cout << "total value after " << N << " loops: " << value[0] << std::endl;
        std::cout << "total time: " << end_t - start_t << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}