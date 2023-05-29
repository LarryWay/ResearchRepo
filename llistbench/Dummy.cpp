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

void inject_fragments(){

    std::random_device r;
    std::default_random_engine dre(r());
    std::uniform_int_distribution<int> repeat_amount(1, 10);
    std::uniform_int_distribution<int> malloc_size(1, 20);

    repeat_for(repeat_amount(dre), [&malloc_size, &dre](){
        malloc(malloc_size(dre));
    }); 

}

// Boilerplate
void initialize_dummy(LinkedList<Dummy>& d){
    std::random_device r;
    std::default_random_engine dre(r());
    std::uniform_int_distribution<int> num_dist(INT32_MIN, INT32_MAX);
    std::uniform_int_distribution<int> letter_dist('a', 'z');
    const int DUMMY_SIZE = 100'000;
    for(int x = 0 ; x < DUMMY_SIZE ; x++){
        inject_fragments();
        Dummy clone(num_dist(dre), letter_dist(dre));
        d.push_back(clone);
        //std::cout << "Created Clone with " << clone.num << "   " << clone.letter << '\n';
    }
}