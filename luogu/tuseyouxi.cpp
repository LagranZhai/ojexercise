#include<iostream>
#include<utility>
using namespace std;
using pii=pair<int,int >;
const int maxnm=1e6;
pii myrow[maxnm+100],myline[maxnm+100];
int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        int n,m,q;
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++){
            myrow[i]=make_pair(0,0);
        }
        for(int i=1;i<=n;i++){
            myline[i]=make_pair(0,0);
        }
        int opt,x,c;
        for(int i=1;i<=q;i++){
            cin>>opt>>x>>c;
            if(opt){
                myrow[x]=make_pair(i,c);
            }
            else{
                myline[x]=make_pair(i,c);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cout<<(myline[i]>myrow[j]?myline[i].second:myrow[j].second)<<' ';
            }
            cout<<'\n';
        }
    }
    cout.flush();
    return 0;
}
