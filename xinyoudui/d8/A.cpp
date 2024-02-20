//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=3e5,maxm=1e6;
struct Edge{
    int v,nxt;
}edg[maxm*2];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int n,m;
int dfx{0},low[maxn],dfn[maxn],scci[maxn],scnt{0};
bool ins[maxn];
std::stack<int> s;
void tarjan(int x){
    low[x]=dfn[x]=++dfx;
    s.push(x);
    ins[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(dfn[to]==0){
            tarjan(to);
            low[x]=std::min(low[x],low[to]);
        }
        else if(!scci[to]){
            low[x]=std::min(low[x],low[to]);
        }
    }
    if(low[x]==dfn[x]){
        ++scnt;
        while(s.top()!=x){
            ins[s.top()]=0;scci[s.top()]=scnt;
            s.pop();
        }
        ins[x]=0;scci[x]=scnt;
        s.pop();
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    char opt1,opt2;int x,y;
    bool flag{1};
    for(int i{1};i<=n;i++){
        cin>>opt1>>x>>opt2>>y;
        if(opt1=='+'){
            if(opt2=='+'){
                addedge(x+m,y);addedge(y+m,x);
            }
            else{
                addedge(x+m,y+m);addedge(y,x);
            }
        }
        else{
            if(opt2=='+'){
                addedge(x,y);addedge(y+m,x+m);
            }
            else{
                addedge(x,y+m);addedge(y,x+m);
            }
        }
    }
    for(int i{1};i<=2*m;i++){
        if(dfn[i]==0)tarjan(i);
    }
    for(int i{1};i<=m;i++){
        if(scci[i]==scci[i+m]){
            flag=0;break;
        }
    }
    if(flag){
        for(int i{1};i<=m;i++){
            cout<<((scci[i]<scci[i+m])?"+ ":"- ");
        }
    }
    else{
        cout<<"IMPOSSIBLE";
    }
    cout<<std::endl;
    return 0;
}