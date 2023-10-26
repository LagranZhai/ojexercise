#include<cstdio>
#include<vector>
using namespace std;

struct s{
	int k;
	int h;
	int p;
	int size;
	vector<int> l;
}tree[1010];
int n,k,a,book[1010],cnt;

int dfs(int i){
	book[i]=1;
	tree[i].h=0;
	tree[i].p=-1;
	for(int j=0;j<tree[i].size;j++){
		if(book[tree[i].l[j]]==0){
			if(dfs(tree[i].l[j])>=tree[i].h){
				if(tree[tree[i].l[j]].h>tree[i].h){
					tree[i].h=tree[tree[i].l[j]].h;
					tree[i].p=tree[i].l[j];
				}
				else if(tree[i].p>tree[i].l[j])tree[i].p=tree[i].l[j];
			}
		}
	}
	tree[i].h+=tree[i].k;;
	return tree[i].h;
}
int main(){
	freopen("apple.in","r",stdin);
	freopen("apple.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		scanf("%d",&a);
		tree[i].size++;
		tree[a].size++;
		tree[a].l.push_back(i);
		tree[i].l.push_back(a);
	}
	
	for(int i=0;i<n;i++)tree[i].k=1;
	cnt=n-1;
	tree[k].k=0;
	printf("%d\n",k);
	while(cnt>0){
		for(int i=0;i<n;i++)book[i]=0;
		dfs(k);
		while(tree[k].p!=-1){
			k=tree[k].p;
			cnt-=tree[k].k;
			tree[k].k=0;
		}
		printf("%d\n",k);
	}
	return 0;
}
