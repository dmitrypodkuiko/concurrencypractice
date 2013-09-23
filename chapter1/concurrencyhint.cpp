#include <iostream>
#include <thread>


int main()
{
    int number_of_threads = std::thread::hardware_concurrency();
    std::cout<< "Number of threads available to run:" << number_of_threads << "\n"; 
    return 0;
}
