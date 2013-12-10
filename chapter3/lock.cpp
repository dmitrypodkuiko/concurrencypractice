class some_big_object{
    void some_big_object(int i){
        this.i = i;
    }
public:
    int i;
};

void swap(some_big_object& lhs, some_big_object& rhs){
    int tmp = some_big_object.i
}

class X
{
private:
    some_big_object some_detail;
    std::mutex m;
public:
    X(some_big_object const & sd):some_detail(sd){}

    friend void swap(X& lhs, X& rhs)
    {
        if(&lhs==&rhs)
        {
           //this is a check to see if we already hold &lhs
           //and don't try to aquire it
           //otherwise it is undefined behaviour
           return;
        }
        std::lock(lhs.m, rhs.m);
        //adopt_lock tells not try and lock mutex that is already locked
        std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(hrs.m,std::adopt_lock);
        swap(lhs.some_detail, rhs.some_detail);
    }


};
