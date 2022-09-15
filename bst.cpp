#include<iostream>
using namespace std;
const int maxn=2e5;
struct Node{
	int val;
	Node *fa,*ch[2]/*,m[2]*/;
//	int d[2];
	int siz;
}tree[maxn],*head=&tree[0],*rt=head,*tot=&tree[0];
inline bool chk(Node* cur){return cur==cur->fa->ch[1];}
void insert(int v){
	if(rt==head){
		//cout<<1<<endl;
		rt=++tot;
		rt->fa=head;
		rt->siz=1;
		rt->val=v;
		return;
//		rt->m[0]=rt->m[1]=rt;
	}
	Node *cur=rt,*f=head,*p=rt;
	bool dir=0;
	int dis=0;
	while(1){
		dir=v>cur->val;
		f=cur,cur=cur->ch[dir];	
		dis++;
		if(cur==nullptr){
			cur=++tot;
			cur->fa=f;
			f->ch[v>f->val]=cur;
			cur->val=v;
			cur->siz=1;
			for(;f!=head;f=f->fa){
				f->siz++;
			}
			break;
		}
		if(f->ch[dir^1]!=nullptr&&cur->siz<=f->ch[dir^1]->siz+1)p=cur,dis=0;
		if(p!=cur){
			int dep=1;
			bool rid=p->val<cur->val;
			Node *sre=cur;
			while(sre->ch[rid]!=nullptr)dep++;
			if((p->siz-cur->siz)*dep<cur->siz*dis){
				cur->fa->ch[chk(cur)]=nullptr;
				cur->fa=p->fa;
				cur->fa->ch[chk(p)]=cur;
				p->fa=sre;
				sre->ch[rid]=p;
				for(Node* j=sre;j==cur->fa;j=j->fa){
					j->siz+=p->siz;
				}
				p=cur,dis=0;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	insert(1);
	insert(2);
	insert(3);
	for(Node *i=rt;i!=nullptr;i=i->ch[1])cout<<i->val;
	return 0;
}




