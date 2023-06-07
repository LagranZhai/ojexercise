#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=3e5;
int n,m,c,k;
int col[maxn+10][11];
struct LCT
{
    ll a[maxn+10], sum[maxn + 10];
    int ch[maxn + 10][2], fa[maxn + 10];
    bool tag[maxn + 10];
    inline int chk(int x)
    {
        if (ch[fa[x]][1] == x)
            return 1;
        if (ch[fa[x]][0] == x)
            return 0;
        return -1;
    }
    inline void upsum(int x)
    {
        sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + a[x];
    }
    inline void pushdown(int x)
    {
        if (tag[x])
        {
            swap(ch[x][0], ch[x][1]);
            tag[ch[x][0]] ^= 1;
            tag[ch[x][1]] ^= 1;
            tag[x] = 0;
        }
    }
    void reverse_pushdown(int x)
    {
        if (chk(x) != -1)
            reverse_pushdown(fa[x]);
        pushdown(x);
    }
    void spin(int x)
    {
        int f = fa[x], dir = chk(x), ff = fa[f];
        if (chk(f) != -1)
            ch[ff][chk(f)] = x;
        fa[ch[x][dir ^ 1]] = f;
        ch[f][dir] = ch[x][dir ^ 1];
        fa[f] = x;
        ch[x][dir ^ 1] = f;
        fa[x] = ff;
        upsum(f);
        upsum(x);
    }
    void splay(int x)
    {
        reverse_pushdown(x);
        int f = fa[x];
        while (chk(x) != -1)
        {
            if (chk(f) != -1)
                spin(chk(f) == chk(x) ? f : x);
            spin(x);
            f = fa[x];
        }
    }
    void access(int x)
    {
        int son = 0;
        while (x)
        {
            splay(x);
            ch[x][1] = son;
            upsum(x);
            son = x;
            x = fa[x];
        }
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        tag[x] ^= 1;
    }
    int findroot(int x)
    {
        access(x);
        splay(x);
        int cur = x;
        while (x)
        {
            pushdown(x);
            cur = x;
            x = ch[x][0];
        }
        splay(cur);
        return cur;
    }
    void split(int x, int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }
    void cut(int x, int y)
    {
        if(if_edge(x,y)){
            fa[x] = 0;
            ch[y][0] = 0;
            upsum(y);
        }
    }
    void link(int x, int y)
    {
        makeroot(x);
        if (findroot(y) != x)
            fa[x] = y;
    }
    void update(int x,int y){
        access(x);
        splay(x);
        a[x]=y;
        upsum(x);
    }
    bool if_connect(int x,int y){
        makeroot(x);
        if(x==findroot(y))return 1;
        else return 0;
    }
    bool if_edge(int x,int y){
        split(x, y);
        if (ch[y][0] == x && fa[x] == y && ch[x][1] == 0)
        {
            return 1;
        }
        return 0;
    }
}lct[11];
int crange(auto x){
    for(int i=0;i<=c;i++){
        if(x(i)){
            return c;
        }
    }
    return -1;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>c>>k;
    int u,v,w;
    for(int i=1;i<=n;i++){
        cin>>u;
        crange([&](int c)->bool{lct[c].a[i]=u;return 0;});
    }
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        col[u][w]++;col[v][w]++;
        lct[w].link(u,v);
    }
    int opt;
    for(int i=1;i<=k;i++){
        cin>>opt;
        if(opt==0){
            cin>>u>>v;
            crange([&](int c)->bool{lct[c].update(u,v);return 0;});
        }
        else if(opt==1){
            cin>>u>>v>>w;
            int curc=crange([&](int c)->bool{
                if(lct[c].if_edge(u,v)){
                    return 1;
                }
                return 0;
            });
            if(curc==-1){
                cout<<"No such edge."<<endl;
                continue;
            }
            if(col[u][w]>=2||col[v][w]>=2){
                cout<<"Error 1."<<endl;
                continue;
            }
            if(lct[w].if_connect(u,v)&&(!lct[w].if_edge(u,v))){
                cout<<"Error 2."<<endl;
                continue;
            }
            lct[curc].cut(u,v);
            lct[w].link(u,v);
            col[u][curc]--;col[v][curc]--;
            col[u][w]++;col[v][w]++;
            cout<<"Success."<<endl;
        }
        else if(opt==2){
            cin>>u>>v>>w;
            cut(x,y);
        }
        else if(opt==3){
            
        }
    }
    return 0;
}