#include <iostream>
#include <condition_variable>
#include <mutex>


std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

class data{
    int count = 0;
public:
    
    bool more_data_to_prepare()
    {
        bool return_value = true;
        if(count > 9){
            return_value = false;
        }
        return false;
    }


    chunk_data prepare_data()
    {
        return new chunk_data(count);
    }
    
    void data_preparation_thread()
    {
        while(more_data_to_prepare())
        {
            data_chunk const data=prepare_data();
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(data);
            data_cond.notify_one();
        }
    }
};

    void data_processing_thread()
    {
        while(true)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk,[]{return !data_queue.empty();});
            data_chunk data=data_queue.front();
            data_queue.pop();
            lk.unlock();
            process(data);
            if(is_last_chunk(data))
                break;
        }

    }


class data_chunk{
public:    
    int data;
    void data_chunk(int i)
    {
        data=i;
    }
};

int main()
{
    std::thread data_proc(data_processing_thread);
    std::thread data_prep(data_preparation_thread);

    return 0;
}

