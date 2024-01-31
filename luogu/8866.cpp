#include<bits/stdc++.h>
using namespace std;
// ifstream fin("meow.in");
// ofstream fout("meow.out");
// #define cin fin
// #define cout fout
int a[2000005],p[1000],b[1005];
deque<int>q[1000];
vector<pair<int,int>>ans;
int pos=1,sz;
int cnt[1005];
queue<int>pq0;
void change(int x,int y){
	ans.push_back({x,y});
	if(y==0){
		pq0.push(x);
		if(!q[x].empty() and q[x].back()==a[pos]){
			q[x].pop_back();
			cnt[a[pos]]--;
			if(cnt[a[pos]]==0)sz--,p[a[pos]]=0;
			if(q[x].empty())b[a[pos]]=0;
		}
		else{
			q[x].push_back(a[pos]);
			if(cnt[a[pos]]==0){
				sz++,p[a[pos]]=x;
			}
			cnt[a[pos]]++;
			if(q[x].size()==1)b[a[pos]]=1;
		}
		pos++;
	}
	else{
		pq0.push(x);
		pq0.push(y);
		if(q[x].front()==q[y].front()){
			b[q[x].front()]=0;
			cnt[q[x].front()]-=2;
			if(cnt[q[x].front()]==0){
				sz--,p[q[x].front()]=0;
				b[q[x].front()]=0;
			}
			q[x].pop_front();
			q[y].pop_front();
			
			if(!q[x].empty())b[q[x].front()]=1;
			if(!q[y].empty())b[q[y].front()]=1;
		}
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		pos=1;
		sz=0;
		memset(p,0,sizeof p);
		memset(b,0,sizeof b);
		ans.resize(0);
		int n,m,k;
		cin>>n>>m>>k;
		int sp=n;
		
		while(!pq0.empty())pq0.pop();
		for(int i=1;i<=n;i++){
			if(i!=sp)pq0.push(i);
		}
		int ap[k+5]={0};
		for(int i=1;i<=m;i++){
			cin>>a[i];
			a[i+1]=0;
		}
		for(int i=1;i<=m;i++){
			if(sz==2*(n-1) and !cnt[a[i]]){
				int ti=i;
				for(int j=i+1;j<=m;j++){
					if(a[j]==a[i]){
						for(int w=i+1;w<=j;w++){
							ap[a[w]]=p[a[w]];
						}
						change(sp,0);
							for(int w=i+1;w<=j;w++){
								if(a[w]==a[i])change(sp,0);
								else change(ap[a[w]],0);
							}
							
						i=j;
						break;
					}
					if(b[a[j]]){
						if(ap[q[p[a[j]]].back()]){
							for(int w=i+1;w<=j;w++){
								ap[a[w]]=p[a[w]];
							}
							change(sp,0);
							sp=p[a[j]];
							for(int w=i+1;w<=j;w++){
								change(ap[a[w]],0);
							}
							
							
						}
						else{
							for(int w=i+1;w<=j;w++){
								ap[a[w]]=p[a[w]];
							}
							change(p[a[j]],0);
							for(int w=i+1;w<j;w++){
								change(ap[a[w]],0);
							}
							change(sp,0);
							change(sp,p[a[j]]);
						}
						i=j;
						break;
					}
					else{
						ap[a[j]]^=1;
					}
				}
				for(int j=ti;j<=i;j++){
					ap[a[j]]=0;
				}
				continue;
			}
			if(p[a[i]]){
				if(q[p[a[i]]].back()==a[i]){
					change(p[a[i]],0);
				}
				else{
					change(sp,0);
					change(sp,p[a[i]]);
				}
			}
			else{
				while(!pq0.empty() and (pq0.front()==sp or q[pq0.front()].size()>=2)){
					pq0.pop();
				}
				change(pq0.front(),0);
			}
		}
		
		cout<<ans.size()<<endl;
		
		for(auto it:ans){
			if(it.second==0)cout<<1<<' '<<it.first<<'\n';
			else cout<<2<<' '<<it.first<<" "<<it.second<<'\n';
		}
		assert(pos==m+1);
		for(int i=1;i<=n;i++){
			assert(q[i].empty());
		}
	}
    return 0;
}