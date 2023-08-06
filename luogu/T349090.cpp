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
constexpr int maxn=12;
int n,m;
#define int long long
std::vector<int > q;
int cal(std::vector<int > c,int d){
    for(int i{0};i<c.size();i++){
        c[i]-=d;
    }
    int ans=0;
    for(int i{0};i<c.size();i++){
        ans+=std::abs(c[i]);
    }
    return ans;
}
void solve(int **a){
    for(int i{2};i<=m;i++){
        for(int j{1};j<n;j++){
            if(a[j+1][i]-a[j+1][1]!=a[j][i]-a[j][1]){
                cout<<-1ll<<"\n";
                return ;
            }
        }
    }
    q.clear();
    for(int i{1};i<=n;i++){
        q.push_back(-1ll*a[i][1]);
    }
    q.push_back(0ll);
    for(int i{2};i<=m;i++){
        q.push_back(a[1][i]-a[1][1]);
    }
    int s=q.size();
    std::sort(std::begin(q),std::end(q));
    if(s%2ll==1ll){
        cout<<cal(q,q[s/2])<<"\n";
    }
    else{
        cout<<std::min(cal(q,q[s/2]),cal(q,q[s/2-1]))<<"\n";
    }
    return ;
}
signed main(){
    //freopen("ex_b2.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie();
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        int** a=new int*[n+1];
        for(int i{0};i<=n;i++){
            a[i]=new int[m+1];
        }
        // int** b=new int[n+1];
        // for(int i{0};i<=n;i++){
        //     b[i]=new int[m+1];
        // }
        for(int i{1};i<=n;i++){
            for(int j{1};j<=m;j++){
                cin>>a[i][j];
            }
        }
        int t;
        for(int i{1};i<=n;i++){
            for(int j{1};j<=m;j++){
                cin>>t;
                a[i][j]-=t;
            }
        }
        solve(a);
        for(int i{0};i<=n;i++){
            delete[] a[i];
        }
        delete[] a;
        // for(int i{0};i<=n;i++){
        //     delete[] b[i];
        // }
        // delete[] b;
    }
    cout.flush();
    return 0;
}
