#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<stack>
#include<cstdlib>
#include<ctime>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=1300;
std::stack<int > a,b,c;
std::stack<int >* snum[maxn+100];
int tot,ans=0;
char stacktoc(std::stack<int >* s) {
    if(s==&a)return 'A';
    if(s==&b)return 'B';
    if(s==&c)return 'C';
}
void singlemv(std::stack<int >* a,std::stack<int >* b) {
    ans++;
    cout<<stacktoc(a)<<" "<<stacktoc(b)<<"\n";
    snum[a->top()]=b;
    b->push(a->top());
    a->pop();
}
void mv(int n,std::stack<int >* a,std::stack<int >* b) {
    if(n==0){
        return ;
    }
    while(a->top()!=n){
        if(rand()%4==1)singlemv(a,&c);
        else singlemv(a,b);
    }
    while(!c.empty()&&c.top()!=n+1){
        singlemv(&c,b);
    }
    singlemv(a,&c);
    mv(n-1,snum[n-1],(snum[n-1]==a)?b:a);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    srand(time(nullptr));
    cin>>tot;
    {
        int t;
        for(int i{1};i<=tot;i++){
            cin>>t;
            b.push(t);
        }
    }
    while(!b.empty()){
        snum[b.top()]=&a;
        a.push(b.top());
        b.pop();
    }
    // for(int i{1};i<=tot;i++){
    //     std::cout<<a.top()<<" "<<std::flush;
    //     a.pop();
    // }
    // for(int i{1};i<=tot;i++){
    //     std::cout<<stacktoc(snum[i])<<" "<<std::flush;
    // }
    mv(tot,&a,&b);
    //std::cout<<tot<<"\n";
    std::cout<<ans<<"\n";
    cout.flush();
    return 0;
}
