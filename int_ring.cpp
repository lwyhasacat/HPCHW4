#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    // int value = 0;
    double start_t, end_t;

    // below for array
    const int array_size = 500000; // about 2 mbytes
    double value[array_size] = {}; // initialize the array with zeros

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

    // for array 
    // for(int i = 0; i < N; i++) {
    //     if(rank == 0) {
    //         MPI_Send(value, array_size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    //         MPI_Recv(value, array_size, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //         for(int j = 0; j < array_size; j++) {
    //             value[j] += rank;
    //         }
    //     } 
    //     else{
    //         MPI_Recv(value, array_size, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //         for(int j = 0; j < array_size; j++) {
    //             value[j] += rank;
    //         }
    //         MPI_Send(value, array_size, MPI_DOUBLE, (rank + 1) % size, 0, MPI_COMM_WORLD);
    //     }
    // }

    // for integer
    for (int i = 0; i < N; i++) {
        if (rank == 0) {
            MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            value += rank;
        } else {
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            value += rank;
            MPI_Send(&value, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }
    }

    end_t = MPI_Wtime();

    // for array
    // if (rank == 0) {
    //     std::cout << "total value after " << N << " loops: " << value[0] << std::endl;
    //     std::cout << "total time: " << end_t - start_t << " seconds" << std::endl;
    // }

    // for int
    if (rank == 0) {
        std::cout << "total value after " << N << " loops: " << value << std::endl;
        std::cout << "total time: " << end_t - start_t << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
