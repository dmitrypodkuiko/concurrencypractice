#include <iostream>
#include <thread>
#include <assert.h>
void do_background_work()
{
    for (int i = 0; i <= 100000; i++)
    {
        int j = i+1;
    }
}

int main()
{
    std::thread t(do_background_work);
    t.detach();
    assert(t.joinable()); //should fail  

    return 0;
}
