#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define Be begin()
#define En end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),I=(b);i<I;i++)
#define L(i,a,b) for(int i=(b)-1,I=(a)-1;i>I;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=2e7;
ll ansz,ansp;
string a,b;

//Zfunction
int z[N<<1];
void getz(string s){
    int l=0;
    R(i,1,sz(s)){
        if(l+z[l]>i) z[i]=min(z[i-l],l+z[l]-i);
        while(i+z[i]<sz(s)&&s[z[i]]==s[i+z[i]]) z[i]++;
        if(i+z[i]>l+z[l]) l=i;
    }
    // R(i,0,sz(s)) cout<<z[i]<<" ";cout<<'\n';
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    freopen("P5410_2.in","r",stdin);	
	
    cin>>a>>b,getz(b+a);
    ansz^=1ll*(sz(b)+1)*(0+1);
    R(i,1,sz(b)) ansz^=1ll*(min(z[i],sz(b)-i)+1)*(i+1);
    R(i,0,sz(a)) ansp^=1ll*(min(z[i+sz(b)],sz(b))+1)*(i+1);
    cout<<ansz<<'\n'<<ansp<<'\n';
    return 0;
}
