#include <iostream>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>

struct empty_stack: std::exception
{
    std::string s;
    empty_stack(std::string ss) : s(ss){}
    ~empty_stack() throw (){}
    const char* what() const throw(){return s.c_str();}
};

template<typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty())
            throw empty_stack("empty stack exception");
        std::shared_ptr<T> const res(std::make_shared<T> (data.top()));
        data.pop();
        return res;
    }

    void pop(T& value)
    {
        std:: lock_guard<std::mutex> lock(m);
        if(data.empty()) 
            throw empty_stack("empty stack exception");
        value = data.top();
        data.pop();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

void pusher(threadsafe_stack<int> & stack)
{
    for(int i = 0; i < 100; i++)
    {
        stack.push(i);
    }
}

void popper(threadsafe_stack<int> & stack)
{

    for(int i = 0; i< 100; i++)
    {    
        stack.pop();
    }
}

int main()
{
    threadsafe_stack<int> stack;
    stack.push(5);
    stack.push(23);
    stack.push(11);
    std::thread t(pusher,std::ref(stack));
    t.join();

    std::chrono::milliseconds duration(2000);
    std::this_thread::sleep_for(duration);

    for(int i = 104;i>=0;i--){
        try{
            std::shared_ptr<int>  j = (stack.pop());
            std::cout<<*j<<","<<std::endl;
        }catch(empty_stack& caught){
            std::cout<<"Got "<<caught.what()<<std::endl;
        }
    }
    return 0;
}





