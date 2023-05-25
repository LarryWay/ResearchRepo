/*

    Goal: Benchmark the speeds required to "read" an item
    in a Linked List from the first item to the last item

*/


#include "../time_utils.cpp"
#include "LinkedList.cpp"
#include "Dummy.cpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <array>




int main(){

    Dummy one(INT32_MIN, 'a');
    Dummy two(INT32_MAX, 'z');

    LinkedList<Dummy> list{one, two};
    initialize_dummy(list);

    constexpr int array_size = 100'000 / 1'000;
    std::array<int, array_size> frag_at;
    std::array<int, array_size> defrag_seq_at;
    std::array<int, array_size> defrag_at; 

    for(int x = 0 ; x < list.size ; x += 1'000){
        std::cout << avg_time<std::chrono::nanoseconds>([&x, &list](){ list.at(x).stall(); }).count() << '\n';
        frag_at[x / 1'000] = avg_time<std::chrono::nanoseconds>([&x, &list](){ list.at(x).stall(); }).count();
    }

    //list.defragment();

    std::cout << "END OF MANUAL AT" << std::endl;
    std::cout << "Time to defrag: " << time<std::chrono::nanoseconds>([&list](){ list.defragment(); }).count() << '\n';

    for(int x = 0 ; x < list.size ; x += 1'000){
        std::cout << avg_time<std::chrono::nanoseconds>([&x, &list](){ list.seq_at(x).stall(); }).count() << '\n';
        defrag_seq_at[x / 1'000] = avg_time<std::chrono::nanoseconds>([&x, &list](){ list.seq_at(x).stall(); }).count();
    }

    std::cout << "END OF SEQ AT" << '\n';

    for(int x = 0 ; x < list.size ; x += 1'000){
        std::cout << avg_time<std::chrono::nanoseconds>([&x, &list](){ list.at(x).stall(); }).count() << '\n';
        defrag_at[x / 1'000] = avg_time<std::chrono::nanoseconds>([&x, &list](){ list.at(x).stall(); }).count();
    }

    for(int x = 0 ; x < array_size ; x++){
        std::cout << frag_at[x] << " , " << defrag_seq_at[x] << " , " << defrag_at[x] << '\n';
    }


}