//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=6000,maxm=1e6,maxl=300,maxc=30;
struct Edge{
    int v,nxt;
}edg[maxm];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
bool isnum(const std::string &s,int l,int r){
    for(int i{l};i<=r;i++){
        char a=s[i];
        if(a<'0'||a>'9'){
            return false;
        }
    }
    return true;
}
std::string s[maxl][maxc];
int n,m;
int dp[maxn],in[maxn];
using pii=std::pair<int,int>;
std::vector<pii> g[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>s[i][j];
            if(isnum(s[i][j],0,s[i][j].size()-1)){
                dp[(i-1)*m+j]=atoll(s[i][j].c_str());
            }
            else{
                int p{0},opt{1};
                while(p<s[i][j].size()){
                    int op{p};
                    while(p<s[i][j].size()&&s[i][j][p]!='+'&&s[i][j][p]!='-')p++;
                    if(!isnum(s[i][j],op,p-1)){
                        int y{s[i][j][op]-'A'+1};
                        int x{atoll(s[i][j].substr(op+1,p-op-1).c_str())};
                        addedge((x-1)*m+y,(i-1)*m+j);
                        g[(i-1)*m+j].push_back({(x-1)*m+y,opt});
                        in[(i-1)*m+j]++;
                    }
                    else{
                        int num{atoll(s[i][j].substr(op,p-op).c_str())};
                        dp[(i-1)*m+j]+=opt*num;
                    }
                    if(p==s[i][j].size()){
                        break;
                    }
                    else{
                        opt=((s[i][j][p]=='+')?1:-1);
                    }
                    p++;
                }
            }
        }
    }
    std::queue<int> q;
    for(int i{1};i<=n*m;i++){
        if(in[i]==0)q.push(i);
    }
    while(!q.empty()){
        int cur{q.front()};q.pop();
        for(pii a:g[cur]){
            dp[cur]+=a.second*dp[a.first];
        }
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            in[to]--;
            if(in[to]==0)q.push(to);
        }
    }
    // bool flag{0};
    // for(int i{1};i<=n*m;i++){
    //     if(in[i]){
    //         flag=1;break;
    //     }
    // }
    // if(flag){
    //     cout<<"1 1\nERROR\n";
    // }
    // else{
        cout<<n<<" "<<m<<"\n";
        for(int i{1};i<=n;i++){
            for(int j{1};j<=m;j++){
                if(in[(i-1)*m+j]==0){
                    cout<<dp[(i-1)*m+j]<<" ";
                }
                else{
                    cout<<"ERROR"<<" ";
                }
            }
            cout<<"\n";
        }
    // }
    cout.flush();
    return 0;
}