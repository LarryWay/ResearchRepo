#include <iostream>
#include <cassert>


class MemoryPool{

    size_t size;
    size_t ptr_loc;
    std::byte* mem_space;

    public:

        MemoryPool(size_t s) : size{s}, ptr_loc{0}, mem_space((std::byte*) malloc(s)){

        }

        void* allocate(size_t obj_size){
            void* p = (void*) (mem_space + ptr_loc);
            ptr_loc += obj_size;

            if(ptr_loc >= size){
                std::cout << "Out of memory| Size: " << size << " | ptr_loc: " << ptr_loc << std::endl;
                return nullptr;
            }

            return p;
        }

        void release(){
            ptr_loc = 0;
            free(mem_space);

        }

};