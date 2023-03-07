#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4,maxm=1e5;
int fa[maxn*2],e[maxn];
int n,m;
struct Rel{
    int a,b,c;
}rela[maxm+1000];
struct Com{
    bool operator()(const Rel A,const Rel B)const{
        return A.c>=B.c;
    }
};
int findf(int x){
    return fa[x]=(fa[x]==x)?x:findf(fa[x]);
}
void merge(int u,int v){
    int uf=findf(u),vf=findf(v);
    fa[uf]=vf;
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int a,b,c;
    for(int i=1;i<=m;i++){
        cin>>a>>b>>c;
        rela[i].a=a;
        rela[i].b=b;
        rela[i].c=c;
    }
    sort(rela+1,rela+1+m,Com());
    for(int i=1;i<=n;i++)fa[i]=i;
    int num=0;
    // pri[0]=rela[1].a;pri[1]=rela[1].b;
    // cout<<rela[1].c<<endl;
    for(int i=1;i<=m;i++){
        int ca=rela[i].a,cb=rela[i].b,cc=rela[i].c,
            af=findf(ca),bf=findf(cb);
        if(af==bf){
            num=cc;
            break;
        }
        if(!e[ca])e[ca]=cb;
        else merge(cb,e[ca]);
        if(!e[cb])e[cb]=ca;
        else merge(ca,e[cb]);
    }
    cout<<num<<endl;
    return 0;
}