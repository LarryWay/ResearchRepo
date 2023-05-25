#include <iostream>
#include <memory>
#include <utility>


template<typename T_n>
struct Node{

    Node<T_n>* prev_node;
    Node<T_n>* next_node;
    T_n obj;

    Node(T_n& input_obj) : prev_node(nullptr), next_node(nullptr), obj{input_obj}{
    }

    Node() : prev_node(nullptr), obj{}, next_node(nullptr){
    }

    ~Node() = default;

};


template <typename T>
class LinkedList{

    public:
        std::allocator<Node<T>> alloc;
        Node<T>* first_node;
        Node<T>* last_node;
        Node<T>* shell_node;
        size_t size;

    public:
        template <typename T_i>
        struct Iterator{

            Node<T_i>* node;

            Iterator(Node<T_i>* n) : node(n){ } 

            ~Iterator() = default;

            Node<T_i>* node_ptr(){
                return node;
            }

            Node<T_i>* get(){
                return node;
            }

            void operator++(int){
                node = node -> next_node;
            }

            Iterator<T_i> operator=(Iterator<T_i>& i){
                node = i.node;
            }

            T_i& operator*(){
                return (*node).obj;
            }

            bool operator==(Iterator<T_i>& compare_it){
                return node == compare_it.node;
            }

            bool operator!=(Iterator<T_i>& compare_it){
                return node != compare_it.node;
            }

        };

        LinkedList(T& obj1, T& obj2) : size(2){
            first_node = alloc.allocate(2);
            last_node = first_node + 1;

            std::construct_at(first_node, obj1);
            std::construct_at(last_node, obj2);

            first_node -> next_node = last_node;
            last_node -> prev_node = first_node;

            shell_node = alloc.allocate(1);
            std::construct_at(shell_node);

            last_node -> next_node = shell_node;
        }

        ~LinkedList<T>(){
            destroy_chain(first_node, last_node);
            std::destroy_at(shell_node);
        }

        void push_back(T& obj){
            Node<T>* temp_ptr = alloc.allocate(1);
            std::construct_at(temp_ptr, obj);
            last_node -> next_node = temp_ptr;
            temp_ptr -> prev_node = last_node;
            last_node = temp_ptr;

            last_node -> next_node = shell_node;

            size++;
        }

        void destroy_chain(Node<T>* start_ptr, Node<T>* end_ptr){  

            Node<T>* del_ptr = start_ptr;
            Node<T>* future_ptr = start_ptr -> next_node;

            while(del_ptr != end_ptr){
                std::destroy_at(del_ptr);
                del_ptr = future_ptr;
                future_ptr = future_ptr -> next_node;
            }
        }

        void destroy_chain(std::pair<Node<T>*, Node<T>*> pair){
            destroy_chain(pair.first, pair.second -> next_node);
        }


        void defragment(){

            LinkedList::Iterator<T> it = begin();

            std::pair<Node<T>*, Node<T>*> del_pair = std::make_pair(first_node, last_node);

            Node<T>* temp_ptr = alloc.allocate(size);
            std::construct_at(temp_ptr, *it);
            it++;
            
            for(size_t x = 1 ; x < size - 1 ; x++){
                std::construct_at(temp_ptr + x, *it);
                (temp_ptr + x) -> prev_node = (temp_ptr + (x - 1));
                (temp_ptr + (x - 1)) -> next_node = (temp_ptr + x);
                it++;
            }

            std::construct_at(temp_ptr + (size - 1), *it);
            (temp_ptr + (size - 1)) -> prev_node = (temp_ptr + (size - 2));
            (temp_ptr + (size - 2)) -> next_node = (temp_ptr + (size - 1));

            first_node = temp_ptr;
            last_node = (temp_ptr + (size - 1));

            last_node -> next_node = shell_node;
            shell_node -> prev_node = last_node;

            destroy_chain(del_pair);

        }
        

        void print_list(){
            
            int count = 1;
            for(auto it = begin() ; it != end() ; it++){
                std::cout << "------------------------------\n";
                std::cout << "| Node Number: " << count << '\n';
                std::cout << "| Prev Node: " << it.node_ptr() -> prev_node << '\n';
                std::cout << "| Curr Addr: " << it.node_ptr() << '\n';
                std::cout << "| -Obj Addr: " << &(it.node_ptr() -> obj) << '\n';
                std::cout << "| Next Node: " << it.node_ptr() -> next_node << '\n';
                count++;
            }

            std::cout << "------------------------------\n";

        }


        T& seq_at(int index){
            return ((first_node + index) -> obj);
        }

        T& at(int index){
            auto trav_it = begin();

            for(int i = 0 ; i < index ; i++){
                trav_it++;
            }

            return (trav_it.get() -> obj);
        }

        Iterator<T> begin(){
            return Iterator<T>(first_node);
        }

        Iterator<T> end(){
            return Iterator<T>(last_node -> next_node);
        }

};