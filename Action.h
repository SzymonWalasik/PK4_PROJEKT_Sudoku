#include <vector>;
#include <functional>;

using namespace std;


class Action        
{
private:
    void Empty();
    vector<function<void()>> funcPtrs;      //zbiera wszystkie wskaüniki do funkcji click

public:
    void operator()()
    {
       for (auto f : funcPtrs) 
        f(); 
    }

    void operator+=(function<void()> f)
    {
       funcPtrs.push_back(f);
    }
};


