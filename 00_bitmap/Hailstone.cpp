#include <iostream>
using namespace std;

template <typename T> struct Hailstone{
    virtual void operator()(T& e){
        int step = 0;
        while(!= e){
            e = e%2 ? 3*e+1 : e/2;
            step++;
        }
        e = step;
    }
};

int main(){
    int i_number = 26;
    Hailstone<int> hailstone_int;

    cout << "Hailstone sequence steps for " << i_number << ": ";
    hailstone_int(i_number);
    cout << "The number of steps required is :" << i_number << endl;

    return 0;
}