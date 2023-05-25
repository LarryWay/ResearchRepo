#include <iostream>
#include <functional>
#include "LinkedList.cpp"


#include <iostream>
#include <chrono>
#include <functional>



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
double time(std::function<void()> f){
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<T>(end - start).count();
}

void repeat_for(int iterations, std::function<void()> f){
    for(int x = 0 ; x < iterations ; x++){
        f();
    }
}



int main(){

    int temp1 = 5;
    int temp2 = 6;
    LinkedList<int> list{temp1, temp2};

    repeat_for(1000, [&list](){
        int val = 6;
        list.push_back(val);
    });

    double n = time<std::chrono::milliseconds>([&list](){
       list.at(999); 
    });

    std::cout << n << std::endl;


}