#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <chrono>
#include <iomanip>

void NxNGenerator(int64_t, int64_t***);

void Multiplier(size_t, int64_t***);

void Matrix_Print(int64_t **, size_t);

void MemFree(int64_t**, int64_t);


int main(int argc, char *argv[]) {
  if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <size_of_matrice>\n", argv[0]);
        return EXIT_FAILURE;
    };
  int64_t N = atoi(argv[1]);

  auto start = std::chrono::high_resolution_clock::now();

  int64_t *** Matrix_PTRS = (int64_t***)malloc(2*sizeof(int64_t**));
  
  NxNGenerator(N, Matrix_PTRS);

  Multiplier(N, Matrix_PTRS);
  
  delete[] Matrix_PTRS;

  auto end = std::chrono::high_resolution_clock::now();
  double time_taken = 
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
 
    time_taken *= 1e-9;
 
    std::cout <<std::fixed 
         << time_taken << std::setprecision(9);
    std::cout << std::endl;
  
  return 0;
}


void NxNGenerator(int64_t N, int64_t*** Matrix_PTRS){
  int64_t **M1, **M2;

  M1 = (int64_t**)malloc(N*sizeof(int64_t*));
  M2 = (int64_t**)malloc(N*sizeof(int64_t*));


  // Seed the random number generator with current time
  srand(time(nullptr));

  
  for (size_t x = 0; x < N; x++) {
    M1[x] = (int64_t*)malloc(N*sizeof(int64_t));
    M2[x] = (int64_t*)malloc(N*sizeof(int64_t));

    for (size_t y = 0; y < N; y++){
      M1[x][y] = rand() % 5;
      M2[x][y] = rand() % 5;
    }
  }
  

  // Matrix_Print(M1,N);
  // Matrix_Print(M2,N);

  Matrix_PTRS[0] = M1;
  Matrix_PTRS[1] = M2;
}


void Multiplier(size_t N, int64_t***Matrix_PTRS) {

  int64_t **M3 = (int64_t**)malloc(N*sizeof(int64_t*));

  for(size_t x =0; x< N ; x++){
    M3[x] = (int64_t*)malloc(N*sizeof(int64_t));
    memset(M3[x], 0 ,sizeof(M3[x]));              

    for(size_t y =0; y< N; y++){
      for(size_t k =0; k< N; k++){
        M3[x][y]+=Matrix_PTRS[0][k][y]*Matrix_PTRS[1][x][k];

      }
    }
  }

  // Matrix_Print(M3, N);

  MemFree(Matrix_PTRS[0],N);
  MemFree(Matrix_PTRS[1],N);
  MemFree(M3,N);  
}


void Matrix_Print(int64_t ** arr, size_t N){
  for(size_t y = 0 ; y < N ; y++){
    for(size_t x = 0 ; x < N ; x++){
      std::cout<<arr[x][y]<<" ";
    }
    std::cout<<"\n";
  }

  std::cout << "--------------------------\n" << std::endl;
  return;
}

void MemFree(int64_t** arr, int64_t N){
  for(int64_t i = 0; i< N; i++){
    free(arr[i]);
  }
}