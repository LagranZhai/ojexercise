#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<vector>
#include<map>
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
constexpr int maxn=1e5,maxm=2e5;
int n,m;
std::vector<std::tuple<int,int,int> > que;
std::vector<std::tuple<int,int,int> > opt;
int fa[maxn*2],v[maxn*2];
int fe[maxm+100],ve[maxm+100],fbegin[maxm+100];
//int qmap[maxm+100];
int findf(int x){
    return fa[x]==x?x:(fa[x]=findf(fa[x]));
}
std::map<std::pair<int,int >,int > qmap;
int main(){
    // freopen("dcgsample3.in","r",stdin);
    // freopen("dcgsample3.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    int flag=0;
{
    int o,x,y;
    for(int i{1};i<=m;i++){
        cin>>o;
        if(o==2){
            cin>>x;
            flag=1;
            opt.push_back(std::make_tuple(o,x,x));
            continue;
        }
        cin>>x>>y;
        opt.push_back(std::make_tuple(o,x,y));
        if(o==3){
            que.push_back(std::make_tuple(i,x,y));
            qmap[std::make_pair(x,y)]=0;
            //qmap[i]=que.size()-1;
        }
    }
}
    for(int i{1};i<=n;i++)fa[i]=i;
    if(flag==0){
        for(int i{1};i<=m;i++){
            int o=std::get<0>(opt[i-1]);
            int x=std::get<1>(opt[i-1]);
            int y=std::get<2>(opt[i-1]);
            if(o==1){
                if(qmap.find(std::make_pair(x,y))!=qmap.end()){
                    qmap[std::make_pair(x,y)]++;
                }
                if(qmap.find(std::make_pair(y,x))!=qmap.end()){
                    qmap[std::make_pair(y,x)]++;
                }
            }
            if(o==3){
                cout<<qmap[std::make_pair(x,y)]<<"\n";
            }
        }
    }
else{
    for(int i{1};i<=m;i++){
        int o=std::get<0>(opt[i-1]);
        int x=std::get<1>(opt[i-1]);
        int y=std::get<2>(opt[i-1]);
        if(o==1){
            int fx=findf(x);
            int fy=findf(y);
            if(fx!=fy){
                fa[fy]=fx;
                for(auto [num,u,v]:que){
                    if((fe[num]==0)&&findf(u)==findf(v)){
                        fe[num]=fx;
                    }
                }
            }
            for(auto [num,u,v]:que){
                if((u==x&&v==y)||(u==y&&v==x)){
                    ve[num]++;
                }
            }            
        }
        if(o==2){
            int fx=findf(x);
            for(auto [num,u,v]:que){
                if(fe[num]&&(findf(fe[num])==fx)){
                    ve[num]++;
                }
            }
        }
        if(o==3){
            cout<<ve[i]<<"\n";
            // auto a=que.begin()+qmap[i];
            // que.erase(a);
        }
    }
}
    cout.flush();
    return 0;
}
