//P3402
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
// #define int long long
constexpr int maxn=1e5,maxm=2e5;
int n,m;
struct hjttree{
    std::function<int(int)> ini{};
    hjttree(std::function<int(int)> x):ini(x){}
    struct Node{
        int ch[2]{},val{};
    }node[maxm*20];
    int root[maxm+10],tot{0};
    void update(int old,int &now,int cl,int cr,const int d,const int v){
        now=++tot;
        node[now]=node[old];
        if(cl==cr){
            node[now].val=v;
            return ;
        }
        int mid{(cl+cr)/2};
        if(d<=mid){
            update(node[old].ch[0],node[now].ch[0],cl,mid,d,v);
        }
        else{
            update(node[old].ch[1],node[now].ch[1],mid+1,cr,d,v);
        }
    }
    int query(int now,int cl,int cr,const int d)const{
        if(cl==cr){
            return node[now].val;
        }
        int mid{(cl+cr)/2};
        if(d<=mid){
            return query(node[now].ch[0],cl,mid,d);
        }
        else{
            return query(node[now].ch[1],mid+1,cr,d);
        }
    }
    void build(int &now,int cl,int cr){
        if(cl==cr){
            now=++tot;
            node[now].val=ini(cl);
            return ;
        }
        now=++tot;
        int mid{(cl+cr)/2};
        build(node[now].ch[0],cl,mid);
        build(node[now].ch[1],mid+1,cr);
        return ;
    }
}fa{[](int x){return x;}},dep{[](int x){return 1;}};
int getfa(int x,int t){
    int f{fa.query(fa.root[t],1,n,x)};
    if(f!=x){
        return getfa(f,t);
    }
    else{
        return x;
    }
}
void merge(int x,int y,int t){//ordinary t
    int fx{getfa(x,t-1)},fy{getfa(y,t-1)};
    if(fx==fy){
        fa.root[t]=fa.root[t-1];
        dep.root[t]=dep.root[t-1];
    }
    else{
        int dx{dep.query(dep.root[t-1],1,n,fx)},dy{dep.query(dep.root[t-1],1,n,fy)};
        if(dy<dx){
            std::swap(fx,fy);
            std::swap(dx,dy);
        }
        fa.update(fa.root[t-1],fa.root[t],1,n,fx,fy);
        if(dx==dy){
            dep.update(dep.root[t-1],dep.root[t],1,n,fy,dy+1);
        }
        else{
            dep.root[t]=dep.root[t-1];
        }
    }
}
void goback(int k,int t){
    fa.root[t]=fa.root[k];
    dep.root[t]=dep.root[k];
}
int query(int a,int b,int t){
    fa.root[t]=fa.root[t-1];
    dep.root[t]=dep.root[t-1];
    int fx{getfa(a,t)},fy{getfa(b,t)};
    if(fx==fy){
        return 1;
    }
    else{
        return 0;
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    fa.build(fa.root[0],1,n);
    dep.build(dep.root[0],1,n);
    int opt,a,b;
    for(int i{1};i<=m;i++){
        cin>>opt;
        if(opt==1){
            cin>>a>>b;
            merge(a,b,i);
        }
        if(opt==2){
            cin>>a;
            goback(a,i);
        }
        if(opt==3){
            cin>>a>>b;
            cout<<query(a,b,i)<<"\n";
        }
    }
    cout.flush();
    return 0;
}