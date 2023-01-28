//4305AC
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
struct Num
{
    int val,ord;
    Num(int _val,int _ord){
        val=_val,ord=_ord;
    }
};
vector<Num> a;
int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        int n,t;cin>>n;
        a.clear();
        for(int i=0;i<n;i++){
            cin>>t;
            a.push_back(Num(t,i));
        }
        sort(a.begin(),a.end(),[](const Num A,const Num B){
            if(A.val==B.val){
                return A.ord<B.ord;
            }
            else return A.val<B.val;
        });
        auto uniquend=unique(a.begin(),a.end(),[](const Num A,const Num B){
            return A.val==B.val;
        });
        sort(a.begin(),uniquend,[](const Num A,const Num B){
            return A.ord<B.ord;
        });
        for(auto i=a.begin();i!=uniquend;i++){
            cout<<i->val<<' ';
        }
        cout<<'\n';
    }
    cout.flush();
    return 0;
}