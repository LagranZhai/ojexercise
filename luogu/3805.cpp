#include<bits/stdc++.h>
using namespace std;
const int maxn=1.1e7;
int p[maxn+100];
void init(string &a){
    string t;
    for(int i=0;i<a.size();i++){
        t.append("#");
        t.append(a.substr(i,1));
    }
    t.append("#");
    a=t;
}
void manacher(string &a,int &ans){
    int mid=0,r=0;
    for(int i=0;i<a.size();i++){
        if(i<r){
            p[i]=min(p[mid*2-i],r-i);
        }
        while(i-p[i]-1>=0&&i+p[i]+1<a.size()&&a[i-p[i]-1]==a[i+p[i]+1])p[i]++;
        if(i+p[i]>r){
            mid=i;
            r=i+p[i];
        }
        ans=max(ans,p[i]);
    }
}
int main(){
    ios::sync_with_stdio(false);
    string s;
    cin>>s;
    init(s);
    int ans=0;
    manacher(s,ans);
    cout<<ans<<endl;
    return 0;
}