#include "../time_utils.cpp"
#include "memorypool.cpp"

const int ALLOC_SIZE = 100;

int main(){

    for(int x = 100 ; x < 100 * 1000 ; x += 1000){
        MemoryPool m((x * 20 * ALLOC_SIZE) + ALLOC_SIZE);
        std::cout << avg_time_iter<std::chrono::nanoseconds>(x, [&m](){ m.allocate(ALLOC_SIZE); }).count() << " , ";
        std::cout << avg_time_iter<std::chrono::nanoseconds>(x, [](){ malloc(ALLOC_SIZE); }).count() << '\n'; // DANGEROUS CODE
        m.release();
    }

    std::cout << "END OF PROGRAM" << std::endl;

}