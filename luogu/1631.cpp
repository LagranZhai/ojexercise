#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+100;
int a[maxn],b[maxn];
priority_queue<int,vector<int>,greater<int> > pq;
int main(){
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i*j>=n)break;
            pq.push(a[i]+b[j]);
        }
    }
    for(int i=0;i<n;i++){
        cout<<pq.top()<<' ';
        pq.pop();
    }
    cout.flush();
    return 0;
}
