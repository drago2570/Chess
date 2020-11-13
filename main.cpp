#include <iostream>
#include "chess.h"

//struct V {
//    V(int i)
//    {
//        std::cout <<"V()\n";
//    }
//    virtual void f() = 0;

//    virtual ~V() {std::cout << "~V()\n";}
//};
//struct A : virtual public V {

//    A(int i) : V(i)
//    {
//        std::cout <<"A()\n";
//    }
//    void f() override {
//        std::cout << "A::f()\n";
//    }

//    virtual ~A() {std::cout << "~A()\n";}
//};
//struct B : virtual public V {

//    B(int i) : V(i)
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
//struct D : public A, public B {
//    D(int i) : V(i), A(i), B(i)
//    {}

//    void f() override {
//        std::cout << "B::f()\n";
//    }

//    virtual ~D() {std::cout << "~D()\n";}
//};

//struct F : public V
//{
//    F(int i) : V(i)
//    {}

//    void f() override {
//        std::cout << "B::f()\n";
//    }

//    virtual ~F() {std::cout << "~F()\n";}
//};


//V* b = new B();
//V* d = new D();
//dynamic_cast<B*>(d)->test();
//delete d;
//delete b;

//    V* d = new D(10);
//    delete d;

int main()
{
    Chess chess;
    std::cout << "size " << sizeof (chess) << std::endl;
    chess.run();

    return 0;
}
