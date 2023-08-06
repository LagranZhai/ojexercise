#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<limits>
#include<stack>
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
constexpr int maxn=1e3;
int n;
int a[maxn*2],rmin[maxn*2];
int head[maxn*2],cnt=0;
struct Edge{
    int v=0,nxt=0;
}edg[maxn*maxn+100];
void addedge(int u_,int v_){
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
int col[maxn*2];
int dfs(int x,int c){
    col[x]=c;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to=edg[e].v;
        if(col[to]==0){
            dfs(to,3-c);
        }
        else if(col[to]==c){
            return 1;
        }
    }
    return 0;
}
std::stack<int > s[2];
void spop(int v,int t,int& now){
    while((!s[t].empty())&&s[t].top()<v){
        if(!s[0].empty()&&now==s[0].top()){
            s[0].pop();
            cout<<"b"<<" ";
        }
        else if(!s[1].empty()&&now==s[1].top()){
            s[1].pop();
            cout<<"d"<<" ";
        }
        now++;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    std::fill(rmin,rmin+maxn*2,std::numeric_limits<int >::max());
    for(int i=n;i>=1;i--){
        rmin[i]=min(rmin[i+1],a[i]);
    }
    for(int i{1};i<=n;i++){
        for(int j{i};j<=n;j++){
            if(a[i]<a[j]&&rmin[j+1]<a[i]){
                addedge(i,j);
                addedge(j,i);
            }
        }
    }
    int sta=0;
    for(int i{1};i<=n;i++){
        if(!col[i]){
            sta=dfs(i,1);
            if(sta)break;
        }
    }
    //std::cerr<<sta;
    if(sta){
        cout<<0<<"\n";
    }
    else{
        int now=1;
        for(int i{1};i<=n;i++){
            if(col[i]==0||col[i]==1){
                spop(a[i],0,now);
                cout<<"a"<<" ";
                s[0].push(a[i]);
            }
            else{
                spop(a[i],1,now);
                while(!s[0].empty()&&s[0].top()==now){
                    s[0].pop();
                    cout<<"b"<<" ";
                    now++;
                }
                cout<<"c"<<" ";
                s[1].push(a[i]);
            }
        }
        spop(n+1,0,now);
        spop(n+1,1,now);
    }
    cout.flush();
    return 0;
}
