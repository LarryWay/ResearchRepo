#include "../time_utils.cpp"
#include "LinkedList.cpp"
#include "Dummy.cpp"

#include <iostream>
#include <chrono>
#include <random>



int main(){

    Dummy one(0, 'c');
    Dummy two(1, 'a');
    LinkedList<Dummy> list{one, two};

    initialize_dummy(list);



}