#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
// using namespace std;
// int cin{0};
constexpr int maxn=5e5,maxw=2e9+1,logn=20;
//#define int long long
using ll=long long;
int n,k,L,R;
ll a[maxn+100];
struct Node{
    int cnt{0};
    int ch[2],pos{0};
}hjt[maxn*32];
int tot{0},root[maxn+100]{0};
void update(int old,int &now,ll cl,ll cr,ll l,int p){
    now=++tot;
    hjt[now]=hjt[old];
    hjt[now].cnt++;
    ll mid=(cl+cr)/2;
    bool dir=l>mid;
    if(cl==cr){
        hjt[now].pos=p;
        return ;
    }
    update(hjt[old].ch[dir],hjt[now].ch[dir],dir?mid+1:cl,dir?cr:mid,l,p);
}
int query(int old,int now,ll cl,ll cr){
    if(cl==cr){
        return hjt[now].pos;
    }
    int c=hjt[hjt[now].ch[0]].cnt-hjt[hjt[old].ch[0]].cnt;
    ll mid=(cl+cr)/2;
    if(c>0){
        return query(hjt[old].ch[0],hjt[now].ch[0],cl,mid);
    }
    else{
        return query(hjt[old].ch[1],hjt[now].ch[1],mid+1,cr);
    }
}
struct line{
    int r,l,cl,cr;
    bool operator<(const line A)const{
        return a[r]-a[l-1]<a[A.r]-a[A.l-1];
    }
};
std::priority_queue<line > q;

//int st[maxn+10][logn],mylog2[maxn+10];
//void init(int n){
//    mylog2[0]=0;
//    mylog2[1]=0;
//    for(int i{2};i<=n;i++){
//        mylog2[i]=mylog2[i/2]+1;
//    }
//    //return ;
//    int len=mylog2[n];
//    for(int l{1};l<=len;l++){
//        int j=1<<(l-1);
//        for(int i{0};i+(1<<(l))-1<=n;i++){
////            st[i][l]=std::min(st[i][l-1],st[i+j-1][l-1]);
//            if(a[st[i][l-1]]<=a[st[i+j][l-1]]){
//                st[i][l]=st[i][l-1];
//            }
//            else{
//                st[i][l]=st[i+j][l-1];
//            }
//        }
//    }
//    return ;
//}
//int que(int l,int r){
//    int len=mylog2[(r-l+1)];
//    if(a[st[l][len]]<=a[st[r-(1<<len)+1][len]]){
//        return st[l][len];
//    }
//    else{
//        return st[r-(1<<len)+1][len];
//    }
////    return std::min(st[l][len],st[r-(1<<len)+1][len]);
//}
void split(int r,int cl,int cr){//
    if(r-L+1<cl||r-R+1>cr||cl>cr){
        return ;
    }
    int left=r-R+1>=cl?r-R+1:cl;
    int right=r-L+1>=cr?cr:r-L+1;
//    int l{que(left-1,right-1)+1};
    int l{query((left-2>=0)?root[left-2]:0,root[right-1],1,maxw)+1};
    // if(l<left||l>right)std::cerr<<r<<"a";
    q.push({r,l,left,right});
//    std::cerr<<r<<" "<<l<<" "<<left<<" "<<right<<"\n";
}
signed main(){
//    freopen("P2048_1.in","r",stdin);
    ios::sync_with_stdio(false);
    cin>>n>>k>>L>>R;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        a[i]+=a[i-1];
//        st[i][0]=i;
    }
//    init(n);
//    for(int i{0};i<=n;i++){
//        split(i,1,i);
//    }
    int xyz=0;
    update(0,root[0],1,maxw,1e9+1,0);
    for(int i{1};i<=n;i++){
        // cin>>a[i];
        update(root[i-1],root[i],1,maxw,a[i]+1e9+1,i);
        split(i,1,i);
    }
//    std::cerr<<hjt[0].cnt<<"init";
    int num{0};
    ll ans{0};
    while(num<k){
        line cur=q.top();
        q.pop();
        ans+=a[cur.r]-a[cur.l-1];
//        std::cerr<<cur.l<<" "<<cur.r<<"\n";
        split(cur.r,cur.cl,cur.l-1);
        split(cur.r,cur.l+1,cur.cr);
        num++;
    }
    cout<<ans<<std::endl;
    return 0;
}