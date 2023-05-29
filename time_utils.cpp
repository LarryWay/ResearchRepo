#pragma once

#include <iostream>
#include <chrono>
#include <functional>


const int AVERAGE_REPEAT_AMOUNT = 5;


double time_nano(std::function<void()> f){
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double time_milli(std::function<void()> f){
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

template <typename T>
T time(std::function<void()> f){
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<T>(end - start);
}

void repeat_for(int iterations, std::function<void()> f){
    for(int x = 0 ; x < iterations ; x++){
        f();
    }
}


template <typename T>
T time_iter(int iterations, std::function<void()> f){
    return time<T>([&](){
        repeat_for(iterations, f);
    });
}


// Return average time it takes to run the function, f, iterations amount of time
// e.g. average time it takes to run f 1000 times
template <typename T>
T avg_time_iter(int iterations, std::function<void()> f){

    T sum = T::zero();

    for(int x = 0 ; x < AVERAGE_REPEAT_AMOUNT ; x++){
        sum += time_iter<T>(iterations, f);
        //std::cout << sum.count() << std::endl;
    }

    sum = sum / AVERAGE_REPEAT_AMOUNT;
    return sum;

}

template <typename T>
T avg_time(std::function<void()> f){
    T sum = T::zero();

    for(int x = 0 ; x < AVERAGE_REPEAT_AMOUNT ; x++){
        sum += time<T>(f);
    }

    sum /= AVERAGE_REPEAT_AMOUNT;
    return sum;
}