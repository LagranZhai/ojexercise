#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
int n,m;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
struct Que{
    int v{0},ans{0};
}qs[maxn*2];
std::vector<int> que[maxn*2];
int siz[maxn*2];
bool vis[maxn*2];
void dfs1(int x,int f){
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&!vis[to]){
            dfs1(to,x);
            siz[x]+=siz[to];
        }
    }
}
using pii=std::pair<int,int> ;
pii dfs2(int x,int f,int sumsiz){
    int maxss=sumsiz-siz[x];
    pii res={n*2,0};
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&!vis[to]){
            res=std::min(res,dfs2(to,x,sumsiz));
            maxss=std::max(maxss,siz[to]);
        }
    }
    res=std::min(std::make_pair(maxss,x),res);
    return res;
}
int getct(int x){
    dfs1(x,0);
    return dfs2(x,0,siz[x]).second;
}
int c[maxn*2]/*,d[maxn*2]*/;
// std::vector<int> undo,undo2;
// void dfs3(int x,int f,int dep){
//     undo.push_back(dep);undo2.push_back(dep);
//     c[dep]++;d[dep]++;
//     for(int e{head[x]};e;e=edg[e].nxt){
//         int to{edg[e].v};
//         if(to!=f&&!vis[to]){
//             dfs3(to,x,dep+1);
//         }
//     }
// }
// // int ans[maxn*2];
// void dfs4(int x,int f,int dep){
//     if(dep<=que[x]){
//         ans[x]-=d[que[x]-dep];
//     }
//     for(int e{head[x]};e;e=edg[e].nxt){
//         int to{edg[e].v};
//         if(to!=f&&!vis[to]){
//             dfs4(to,x,dep+1);
//         }
//     }
// }
void dfs5(int x,int f,int dep){
    for(int ask:que[x]){
        if(dep<=qs[ask].v){
            qs[ask].ans+=c[qs[ask].v-dep];
        }        
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&!vis[to]){
            dfs5(to,x,dep+1);
        }
    }
}
// void dfs6(int x,int f,int dep){
//     undo.push_back(dep);
//     c[dep]++;
//     for(int e{head[x]};e;e=edg[e].nxt){
//         int to{edg[e].v};
//         if(to!=f&&!vis[to]){
//             dfs6(to,x,dep+1);
//         }
//     }
// }
void dfs7(int x,int f,int dep){
    // undo.push_back(dep);
    c[dep]++;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&!vis[to]){
            dfs7(to,x,dep+1);
        }
    }
}
void dfs8(int x,int f,int dep){
    // undo.push_back(dep);
    c[dep]--;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&!vis[to]){
            dfs8(to,x,dep+1);
        }
    }
}
void calc(int x){
    // std::fill(c,c+maxn*2,0);
    // undo.push_back(0);
    // std::cerr<<x<<"\n";
    c[0]++;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(!vis[to]){
            dfs7(to,x,1);
            // dfs3(to,x,1);
            // dfs4(to,x,1);
            // for(int i:undo2){
            //     d[i]--;
            // }
            // undo2.clear();
        }
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(!vis[to]){
            dfs8(to,x,1);
            dfs5(to,x,1);
            dfs7(to,x,1);
        }
    }
    for(int ask:que[x]){
        qs[ask].ans+=c[qs[ask].v];
    }
    // for(int i:undo){
    //     c[i]--;
    // }
    // undo.clear();
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(!vis[to]){
            dfs8(to,x,1);
        }
    }
    c[0]--;
}
void solve(int x){
    int ct{getct(x)};
    vis[ct]=1;
    calc(ct);
    for(int e{head[ct]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(!vis[to]){
            solve(to);
        }
    }
}
int qcnt{0};
// std::vector<int> q;
int main(){
    // freopen("6626.in","r",stdin);
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        // std::cerr<<T<<"time\n";
        cin>>n>>m;
        int u,v;
        for(int i{1};i<n;i++){
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        for(int i{1};i<=m;i++){
            ++qcnt;
            cin>>u>>v;
            qs[qcnt].v=v;
            que[u].push_back(qcnt);
            // q.push_back(u);
        }
        solve(1);
        for(int i{1};i<=qcnt;i++){
            cout<<qs[i].ans<<"\n";
        }
        std::fill(vis,vis+maxn*2,false);
        std::fill(edg,edg+cnt,Edge{});
        std::fill(qs,qs+maxn*2,Que{});
        std::fill(que,que+maxn*2,std::vector<int>{});
        std::fill(head,head+maxn*2,0);
        // q.clear();
        // std::fill(ans,ans+maxn*2,0);
        qcnt=cnt=0;
    }
    cout<<std::flush;
    return 0;
}