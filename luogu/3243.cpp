#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
struct Graph{
    struct Edge{
        int v{0},nxt{0};
    }edg[maxn*3];
    int head[maxn*2],cnt{0};
    void addedge(int u,int v){
        edg[++cnt]={v,head[u]};
        head[u]=cnt;
    }
    int ind[maxn*2];
}g1;
std::queue<int> q1;
int dp[maxn*2];
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        // std::fill(dp,dp+maxn*2,0);
        g1=Graph{};
        // g2=Graph{};
        // q1=std::queue<int>{};
        std::priority_queue<int> q2;
        int u,v;
        for(int i{1};i<=m;i++){
            cin>>u>>v;
            g1.ind[u]++;
            // g2.ind[v]++;
            g1.addedge(v,u);
            // g2.addedge(u,v);
        }
        // for(int i{1};i<=n;i++){
        //     dp[i]=i;
        //     if(g1.ind[i]==0){
        //         q1.push(i);
        //     }
        // }
        // while(!q1.empty()){
        //     int cur{q1.front()};
        //     q1.pop();
        //     for(int e{g1.head[cur]};e;e=g1.edg[e].nxt){
        //         int to{g1.edg[e].v};
        //         dp[to]=std::min(dp[to],dp[cur]);
        //         g1.ind[to]--;
        //         if(g1.ind[to]==0)q1.push(to);
        //     }
        // }
        for(int i{1};i<=n;i++){
            // cout<<dp[i]<<" ";
            if(g1.ind[i]==0)q2.push(i);
        }
        // cout<<"\n";
        std::vector<int> ans;
        while(!q2.empty()){
            int cur{q2.top()};
            q2.pop();
            ans.push_back(cur);
            for(int e{g1.head[cur]};e;e=g1.edg[e].nxt){
                int to{g1.edg[e].v};
                g1.ind[to]--;
                if(g1.ind[to]==0)q2.push(to);
            }
        }
        if(ans.size()==n){
            for(auto a{ans.rbegin()};a!=ans.rend();a++){
                cout<<*a<<" ";
            }
        }
        else{
            cout<<"Impossible!";
        }
        cout<<std::endl;
    }
    cout.flush();
    return 0;
}