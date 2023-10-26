#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<vector>
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
constexpr int maxn=1000;
int n,ans=0;
std::vector<int > a;
int cnt[2*maxn+100];
void solve(){
    // for(int i{0};i<a.size();i++)std::cerr<<a[i]<<" ";
    // std::cerr<<"\n";
    int b=a[a.size()/2];
    cnt[a[a.size()/2]]=1;
    a.erase(a.begin()+a.size()/2);
    if(a.empty()){
        int c=0;
        for(int i{1};i<=2*n+1;i++){
            if(cnt[i]==1){
                c++;
            }
            else{
                ans=max(ans,c);
                c=0;
            }
        }
    }
    else{
        for(int i{0};i<a.size();i++){
            int t=a[i];
            a.erase(a.begin()+i);
            solve();
            a.insert(a.begin()+i,t);
        }        
    }
    cnt[b]=0;
    a.insert(a.begin()+a.size()/2,b);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    int t;
    int flag=1;
    for(int i{1};i<=n*2+1;i++){
        cin>>t;
        if(t!=i)flag=0;
        a.push_back(t);
    }
    // for(int i{0};i<a.size();i++)std::cerr<<a[i]<<" ";
    // std::cerr<<"\n";    
    if(flag){
        cout<<n+1<<"\n";
    }
    else{
        solve();
        cout<<ans<<"\n";
    }
    cout.flush();
    return 0;
}
