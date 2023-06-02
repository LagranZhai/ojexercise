#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxm=60,maxn=1e5;
vector<int > b;
int a[maxm*2];
map<vector<int >,int > mymap;
signed main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int ans=0;
    int t=0;
<<<<<<< HEAD
=======
    for(int k=1;k<m;k++){
        b.push_back(0);
    }
    mymap.insert(make_pair(b,0));
>>>>>>> 874b0c09da29ee3ae9f5d522da99f33a30cd7e4f
    for(int i=1;i<=n;i++){
        cin>>t;
        int j=0;
        while(t!=0){
            a[m-j-1]+=t%2;
            t/=2;
            j++;
        }
        b.clear();
<<<<<<< HEAD
        for(int k=1;k<=m;k++){
=======
        for(int k=1;k<m;k++){
>>>>>>> 874b0c09da29ee3ae9f5d522da99f33a30cd7e4f
            b.push_back(a[k]-a[k-1]);
        }
        if(mymap.find(b)!=mymap.end()){
            ans=max(ans,i-mymap[b]);
        }
        else mymap.insert(make_pair(b,i));
    }
    cout<<ans<<endl;
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 874b0c09da29ee3ae9f5d522da99f33a30cd7e4f
