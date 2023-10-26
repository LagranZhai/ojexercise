#include<cstdio>
#include<vector>
using namespace std;

vector<int> t1[10010];
vector<int> t2[10010];

int n,a,b,ans;
int size1[10010],size2[10010],tree1[10010],tree2[10010],book1[10010],book2[10010],book3[10010];
int maket1(int k){
	book1[k]=1;
	for(int i=0;i<size1[k];i++){
		if(book1[t1[k][i]]==0){
			maket1(t1[k][i]);
			tree1[t1[k][i]]=k;
		}
	}
	return 0;
}
int maket2(int k){
	book2[k]=1;
	for(int i=0;i<size2[k];i++){
		if(book2[t2[k][i]]==0){
			maket2(t2[k][i]);
			tree2[t2[k][i]]=k;
		}
	}
	return 0;
}

int main(){
	freopen("climb.in","r",stdin);
	freopen("climb.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&a,&b);
		t1[a].push_back(b);
		t1[b].push_back(a);
		size1[a]++;
		size1[b]++;
	}
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&a,&b);
		t2[a].push_back(b);
		t2[b].push_back(a);
		size2[a]++;
		size2[b]++;
	}
	
	maket1(1);
	maket2(1);
	
	for(int i=1;i<=n;i++)book3[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j!=0;j=tree1[j])book3[j]=1;
		for(int j=i;j!=0;j=tree2[j])ans+=book3[j];
		ans--;
	}
	printf("%d",ans);
	return 0;
}
