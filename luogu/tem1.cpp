#include<iostream>
class Mycout{public:
    std::ostream& outs=std::cout;
    template<typename T>
    void output(T x){outs<<x;}
}mycout;
int main(){
    mycout.output(std::flush);
    return 0;
}
