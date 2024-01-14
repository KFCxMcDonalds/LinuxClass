#include <iostream>
using namespace std;

template <class T>
class Calculator
{
    public:
        T add(T a, T b);
        T multiply(T a, T b);
};

template<class T>
T Calculator<T>::add(T a, T b){
    T res;
    res = a + b;
    return res;
}
template <class T>
T Calculator<T>::multiply(T a, T b){
    T res;
    res = a * b;
    return res;
}

// int main()
// {
//     Calculator<float> calculator;
//     float a, b;
//     a = 3.0;
//     b = 15.5;
// 
//     cout << a << " + " << b << " = " << calculator.add(a, b) << endl;
//     cout << a << " * " << b << " = " << calculator.multiply(a, b) << endl;
// 
//     return 0;
// }


 
