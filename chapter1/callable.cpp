#include <iostream>
#include <thread>

class background_task
{
public:
    void operation() () const
    {
        hello();
    }


    void hello()
    {
        std::cout<<"Hello world!";
    }
};

int main()
{
    background_task f;
    std::thread t(f);
    t.join();
    return 0;
}
