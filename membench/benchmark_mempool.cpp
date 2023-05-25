#include "../time_utils.cpp"
#include "memorypool.cpp"


int main(){

    for(int x = 100 ; x < 100 * 1000 ; x += 1000){
        MemoryPool m(x * 20 + 1);
        //std::cout << avg_time_iter<std::chrono::nanoseconds>(x, [&m](){ m.allocate(1); }).count() << std::endl;
        std::cout << avg_time_iter<std::chrono::nanoseconds>(x, [&m](){ m.allocate(1); }).count() << " , ";
        std::cout << avg_time_iter<std::chrono::nanoseconds>(x, [](){ malloc(100); }).count() << '\n'; // DANGEROUS CODE
        m.release();
    }

    std::cout << "End of that" << std::endl;

}