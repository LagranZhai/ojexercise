#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<queue>
using std::cin;
using std::ios;
using std::cout;
constexpr int maxn=1e7,maxm=2e5;
int n;
int cnt[maxm+100];
std::queue<long long > v1,v2;
void read(int &x){ 
	int f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=f;
}
signed main(){
    cin.tie(nullptr);
    read(n);
    int t;
    for(int i{1};i<=n;i++){
        read(t);
        cnt[t]++;
    }
    for(int i{1};i<=maxm;i++){
        if(cnt[i]>=1){
            for(int j{1};j<=cnt[i];j++){
                v1.push(i);
            }
        }
    }
    long long ans=0;
    while(1){
        long long oans=ans;        
        if(v2.empty()||(!v1.empty()&&v1.front()<v2.front())){
            if(v2.empty()&&v1.size()==1)break;
            ans+=v1.front();
            v1.pop();
            if(v2.empty()||(!v1.empty()&&v1.front()<v2.front())){
                ans+=v1.front();
                v1.pop();
            }
            else{
                ans+=v2.front();
                v2.pop();
            }
        }
        else{
            if(v1.empty()&&v2.size()==1)break;
            ans+=v2.front();
            v2.pop();
            if(v1.empty()||(!v2.empty()&&v2.front()<v1.front())){
                ans+=v2.front();
                v2.pop();
            }
            else{
                ans+=v1.front();
                v1.pop();
            }
        }
        v2.push(ans-oans);       
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
