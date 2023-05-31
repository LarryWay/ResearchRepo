/* 

    Dummy object for benchmark_linear.cpp
    Serves as a blank object with a stall method to exaggerate timings 

*/

#pragma once

#include <thread>
#include <chrono>
#include <random>
#include "../time_utils.cpp"

struct Dummy{

    int num;
    char letter;

    Dummy(int n, char c) : num{n}, letter{c} { }

    Dummy(const Dummy& d){
        num = d.num;
        letter = d.letter;
    }

    Dummy() : num{0}, letter{' '} { }

    void stall(){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

};


