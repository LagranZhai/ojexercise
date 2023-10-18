#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<queue>
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
constexpr int maxn=1e6;
#define int long long
int n;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
signed main(){
    // ios::sync_with_stdio(false);
    int T;
    T=read();
    while(T--){
        n=read();
        int ans=0;
        int t;
        std::priority_queue<int,std::vector<int >,std::less<int > > s;
        for(int i{1};i<=n;i++){
            t=read();
            s.push(t);
        }
        int st,stt;
        while(s.size()>1){
            st=s.top();s.pop();
            stt=s.top();s.pop();
            ans+=stt;
            s.push(st-stt);
        }
        cout<<ans<<"\n";
        // if(sum%2==0)cout<<"odd\n";
    }
    cout.flush();
    return 0;
}
