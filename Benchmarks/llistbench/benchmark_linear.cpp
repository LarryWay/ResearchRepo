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


const int DUMMY_LIST_SIZE = 100'000;
const int INCREMENT_SIZE = 1'000;


// Replicates fragmented memory behavior
void inject_fragments(){

    std::random_device r;
    std::default_random_engine dre(r());
    std::uniform_int_distribution<int> repeat_amount(1, 10);
    std::uniform_int_distribution<int> malloc_size(1, 20);

    repeat_for(repeat_amount(dre), [&malloc_size, &dre](){
        malloc(malloc_size(dre));
    }); 

}


// Creates a linked list with DUMMY_LIST_SIZE amount of dummys
void initialize_dummy_list(LinkedList<Dummy>& d){
    std::random_device r;
    std::default_random_engine dre(r());
    std::uniform_int_distribution<int> num_dist(INT32_MIN, INT32_MAX);
    std::uniform_int_distribution<int> letter_dist('a', 'z');
    for(int x = 0 ; x < DUMMY_LIST_SIZE ; x++){
        inject_fragments();
        Dummy clone(num_dist(dre), letter_dist(dre));
        d.push_back(clone);
    }
}



int main(){

    Dummy one(INT32_MIN, 'a');
    Dummy two(INT32_MAX, 'z');

    LinkedList<Dummy> list{one, two};
    initialize_dummy_list(list);

    const int array_size = DUMMY_LIST_SIZE / INCREMENT_SIZE;
    std::array<int, array_size> frag_at;
    std::array<int, array_size> defrag_seq_at;
    std::array<int, array_size> defrag_at; 

    for(int x = 0 ; x < list.size ; x += INCREMENT_SIZE){
        frag_at[x / INCREMENT_SIZE] = avg_time<std::chrono::nanoseconds>([&x, &list](){ list.at(x).stall(); }).count();
    }

    std::cout << "Time to defrag: " << time<std::chrono::nanoseconds>([&list](){ list.defragment(); }).count() << '\n';

    for(int x = 0 ; x < list.size ; x += INCREMENT_SIZE){
        defrag_seq_at[x / INCREMENT_SIZE] = avg_time<std::chrono::nanoseconds>([&x, &list](){ list.seq_at(x).stall(); }).count();
    }

    for(int x = 0 ; x < list.size ; x += INCREMENT_SIZE){
        defrag_at[x / INCREMENT_SIZE] = avg_time<std::chrono::nanoseconds>([&x, &list](){ list.at(x).stall(); }).count();
    }

    for(int x = 0 ; x < array_size ; x++){
        std::cout << frag_at[x] << " , " << defrag_seq_at[x] << " , " << defrag_at[x] << '\n';
    }


}