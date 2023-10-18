#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
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
constexpr int maxn=5e5;
int n,m,q;
std::pair<int,int > t[maxn+100],qe[maxn+100];
int a[maxn+100];
int main(){
	ios::sync_with_stdio(false);
    cin>>n>>m>>q;
    int l,r;
    for(int i{1};i<=m;i++){
        cin>>l>>r;
        t[i]=std::make_pair(r,l);
    }
    for(int i{1};i<=q;i++){
        cin>>l>>r;
        qe[i]=std::make_pair(r,l);
        cout<<"NO\n";
    }
    // t[0]={0,0};
    // std::sort(t+1,t+m+1);
    // std::sort(qe+1,qe+q+1);
    // int b=0,e=0;
    // for(int i{1};i<=q;i++){
    //     while(t[e+1].first<=qe[i].first){
    //         a[t[e+1].first+1]-=1;
    //         a[t[e+1].second]+=1;
    //         e++;
    //     }
    //     while(t[b].second<qe[i].second){
    //         a[t[b].first+1]+=1;
    //         a[t[b].second]-=1;
    //         b--;
    //     }
    // }
	cout.flush();
	return 0;
}

