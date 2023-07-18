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
constexpr int maxm=2e3,maxn=1e6;
int cnt[maxm*2],num=0;
int a[maxn+100];
std::deque<int > q;
struct Ans{
    int s,t,l;
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n,m;
    cin>>n>>m;
    int t;
    Ans ans{n+1,n+1,n+1};
    for(int i{1};i<=n;i++){
        cin>>t;
        a[i]=t;
        q.push_back(i);
        if(!cnt[t])num++;
        cnt[t]++;
        while(!q.empty()&&cnt[a[q.front()]]>1){
            cnt[a[q.front()]]--;
            q.pop_front();
        }
        if(num==m){
            if(q.size()<ans.l){
                ans={q.front(),q.back(),(int)q.size()};
            }
        }
    }
    cout<<ans.s<<" "<<ans.t<<"\n";
    cout.flush();
    return 0;
}
