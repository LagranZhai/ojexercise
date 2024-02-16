//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=51,maxp=2061;
std::string t[maxn];
int n;
int xx1,yy1,x2,y2;
struct Point{
    int x,y;
    bool operator==(const Point& A){
        if(x==A.x&&y==A.y){
            return true;
        }
        return false;
    }
};
bool map[maxn][maxn];
std::vector<Point> v1,v2;
void dfs(int x,int y,std::vector<Point> &v){
    map[x][y]=1;
    v.push_back({x,y});
    int i{x},j{y};
    if(j>1&&t[i-1][j-2]=='0'&&!map[i][j-1])dfs(x,y-1,v);
    if(i>1&&t[i-2][j-1]=='0'&&!map[i-1][j])dfs(x-1,y,v);
    if(i<n&&t[i][j-1]=='0'&&!map[i+1][j])dfs(x+1,y,v);
    if(j<n&&t[i-1][j]=='0'&&!map[i][j+1])dfs(x,y+1,v);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>xx1>>yy1>>x2>>y2;
    for(int i{0};i<n;i++){
        cin>>t[i];
    }
    dfs(xx1,yy1,v1);
    std::fill(map[0],map[0]+maxn*maxn,0);
    dfs(x2,y2,v2);
    int ans{std::numeric_limits<int>::max()};
    for(Point a:v1){
        if(a==(Point){x2,y2}){
            ans=0;break;
        }
    }
    for(Point a:v1){
        for(Point b:v2){
            // cout<<b.x<<" "<<b.y<<"\n";
            ans=std::min(ans,(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}