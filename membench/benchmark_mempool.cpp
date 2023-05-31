#include "../time_utils.cpp"
#include "memorypool.cpp"

const int ALLOC_SIZE = 100;
const int INCREMENT = 10'000;
const int ROWS_OF_DATA = 100;

int main(){

    for(int x = 10'000 ; x < ROWS_OF_DATA * INCREMENT ; x += INCREMENT){
        MemoryPool m((x * AVERAGE_REPEAT_AMOUNT * ALLOC_SIZE) + ALLOC_SIZE);
        std::cout << avg_time_iter<std::chrono::milliseconds>(x, [&m](){ m.allocate(ALLOC_SIZE); }).count() << " , ";
        std::cout << avg_time_iter<std::chrono::milliseconds>(x, [](){ malloc(ALLOC_SIZE); }).count() << '\n'; // DANGEROUS CODE
        m.release();
    }

    std::cout << "END OF PROGRAM" << std::endl;

}