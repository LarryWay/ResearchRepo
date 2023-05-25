#include <iostream>

#include "LinkedList.cpp"


struct Point{

    int x = 1;
    int y = 2;
    double z = 20.0;

    Point() = default;

    ~Point() = default;

    Point(int a, int b, int c) : x(a), y(b), z(c){
        //std::cout << "Created Point: " << x << " " << y << " " << z << std::endl;
        
    }

    explicit Point(Point& p){
        //std::cout << "Copied Point" << std::endl;
        x = p.x ; y = p.y ; z = p.z;
    }



};


int main(){

    Point p1(5,1,7);
    Point p2(3,2,1);
    Point p3(0,69,10);
    Point p4{4,231,4};
    Point p5{1,42,1};

    LinkedList<Point> list(p1, p2);
    list.push_back(p3);
    list.push_back(p4);
    void* m = malloc(100);
    list.push_back(p5);

    list.defragment();

    list.print_list();

    std::cout << "--------------------End of Program -------------------" << std::endl;

}