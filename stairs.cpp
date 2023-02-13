#include<bits/stdc++.h>
using namespace std;
const int maxn=1e8,maxm=3e5;
int line[maxn+100],row[maxn+100];
int m;int bc[maxm+100],cnt=0;
struct Cmp{
    bool operator()(const int& i, const int& j){
        return i>j;
    }
};
struct Que{
    char c;int a,b;
}que[maxm+100];
vector<vector<int> > v;
vector<vector<int> > u;
inline int rl(int cline,int crow){
    return row[crow]-cline+1+line[cline]-crow+1-1;
}
int main(){
    //freopen("stairs.in","r",stdin);
    //freopen("stairs.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>m;
    char c;int a,b;
    for(int i=1;i<=m;i++){
        cin>>que[i].c;
        if(que[i].c=='+'||que[i].c=='-')cin>>que[i].a>>que[i].b;
        if(que[i].c=='R'){
            cin>>que[i].a;
            bc[i-que[i].a]=++cnt;
        }
        if(que[i].c=='?'){
            cin>>que[i].a;
        }
    }
    for(int i=1;i<=m;i++){
        if(que[i].c=='+'){
            a=que[i].a;b=que[i].b;
            if(bc[i]!=0){
                for(int j=1;j<=row[1];j++){
                    v[bc[i]].push_back(line[j]);
                }
                for(int j=1;j<=line[1];j++){
                    u[bc[i]].push_back(row[j]);
                }
            }
            for(int j=1;j<=a;j++){
                for(int k=1;k<=b;k++){
                    row[line[j]+k]++;
                }
                line[j]+=b;
            }         
        }
        if(que[i].c=='-'){
            a=que[i].a;b=que[i].b;
            for(int j=a;j<=row[1];j++){
                for(int k=0;k<b;k++){
                    if(line[j]-k<0)break;
                    row[line[j]-k]--;
                }
                line[j]-=b;
                line[j]=max(0,line[j]);
            }
        }
        if(que[i].c=='R'){
            a=que[i].a;
            int maxl=v[bc[i-a]].size(),maxr=u[bc[i-a]].size();
            for(int j=1;j<=maxl;j++){
                line[j]=v[bc[i-a]][j];
            }
            for(int j=1;j<=maxr;j++){
                row[j]=u[bc[i-a]][j];
            }
        }
        if(que[i].c=='?'){
            if(bc[i]!=0){
                for(int j=1;j<=row[1];j++){
                    v[bc[i]][j]=line[j];
                }
                for(int j=1;j<=line[1];j++){
                    u[bc[i]][j]=row[j];
                }
            }
            a=que[i].a;
            bool flag=0;
            for(int j=1;j<=row[1];j++){
                if(rl(j,1)>=a&&rl(j,line[j])<=a){
                    int l=1,r=line[j],mid=(l+r)/2;
                    while(l<r){
                        if(rl(j,mid)==a)break;
                        if(rl(j,mid)>a){
                            l=mid+1;
                        }
                        if(rl(j,mid)<a){
                            r=mid-1;
                        }
                        mid=(l+r)/2;
                    }
                    if(rl(j,mid)==a){
                        flag=1;cout<<j<<' '<<mid<<endl;
                    }
                }
                if(flag)break;
            }
            if(flag==0)cout<<-1<<endl;
        }
        for(int j=1;j<=row[1];j++){
            cout<<line[j]<<' ';
        }cout<<endl;
    }
    return 0;
}