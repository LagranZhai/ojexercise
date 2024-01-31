#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
#define int long long
struct dm{
    struct Data{
        int sum{0},cnt{0};
        Data operator+(Data &A){
            return {sum+A.sum,cnt+A.cnt};
        }
    }d{};
    int ch[2]{};
}tree[maxn*30];
int tot;
void update(int &p,int cl,int cr,int v,int d){
    if(p==0){
        p=++tot;
    }
    tree[p].d.sum+=v*d;
    tree[p].d.cnt+=1*d;
    if(cl==cr)return ;
    int mid=(cl+cr)/2;
    if(v<=mid)update(tree[p].ch[0],cl,mid,v,d);
    if(v>mid)update(tree[p].ch[1],mid+1,cr,v,d);
    // tree[p].d=tree[tree[p].ch[0]].d+tree[tree[p].ch[1]].d;
    return ;
}
double bs(int p,int cl,int cr,int v,int num,int sum){
    int mid=(cl+cr)/2;
    if(p==0){
        double dv{v-(num*cl-sum)};
        return dv/(double)(num)+(double)cl;
    }
    if(cl==cr){
        double dv{v-((num+tree[p].d.cnt)*cl-sum-tree[p].d.sum)};
        return dv/(double)(num+tree[p].d.cnt)+(double)cl;
        // return cl;
    }
    if((num+tree[tree[p].ch[0]].d.cnt)*(mid+1)-tree[tree[p].ch[0]].d.sum-sum>=v){
        return bs(tree[p].ch[0],cl,mid,v,num,sum);
    }
    else{
        return bs(tree[p].ch[1],mid+1,cr,v,num+tree[tree[p].ch[0]].d.cnt,sum+tree[tree[p].ch[0]].d.sum);
    }
}
int n,q;
int h[maxn*2];
int rt{0};
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int t;
    for(int i{1};i<=n;i++){
        cin>>h[i];
        update(rt,0,1e9,h[i],1);
    }
    int p,x;
    cout<<std::fixed<<std::setprecision(5);
    for(int i{1};i<=q;i++){
        cin>>t;
        if(t==1){
            cin>>p>>x;
            update(rt,0,1e9,h[p],-1);
            update(rt,0,1e9,x,1);
            h[p]=x;
        }
        if(t==2){
            cin>>p;
            cout<<bs(rt,0,1e9,p,0,0)<<"\n";
        }
    }

    cout<<std::flush;
    return 0;
}