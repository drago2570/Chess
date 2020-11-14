#include <iostream>
#include "chess.h"

//struct V {
//    V()
//    {
//        std::cout <<"V()\n";
//    }
//    virtual void f() = 0;

//    virtual ~V() {std::cout << "~V()\n";}
//};
//struct A : virtual V {

//    A() : V()
//    {
//        std::cout <<"A()\n";
//    }
//    void f() override {
//        std::cout << "A::f()\n";
//    }

//    virtual ~A() {std::cout << "~A()\n";}
//};
//struct B : virtual V {

//    B() : V()
//    {
//        std::cout <<"B()\n";
//    }

//    void f() override {
//        std::cout << "B::f()\n";
//    }

//    void test()
//    {
//        std::cout << "B::test()\n";
//    }

//    virtual ~B() {std::cout << "~B()\n";}

//};
//struct D : A, B {
//    D() : A(), B()
//    {}

//    void f() override {
//        std::cout << "B::f()\n";
//    }

//    virtual ~D() {std::cout << "~D()\n";}
//};


//V* b = new B();
//V* d = new D();
//dynamic_cast<B*>(d)->test();
//delete d;
//delete b;


int main()
{
//    Chess chess;
//    std::cout << "size " << sizeof (chess) << std::endl;
//    chess.run();

    Bishop a(1,7, Color::Black);
    a.GeneratePossibleMoves();

    return 0;
}
