#include <iostream>
#include <thread>

class X
{
public:
    void hello()
    {
        std::cout<<"Hello Concurrent World\n";
    }
};

int main()
{
    X my_x;
    std::thread t(&X::hello,&my_x);
    t.join();
    return 0;
}
