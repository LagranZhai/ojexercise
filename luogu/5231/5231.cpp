//5231 
#include<iostream>
#include<cstdio>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
const int maxm=1e5+5;
const int maxn=1e7+7;
int ch[maxn][4];
bool cnt[maxn];
string s;
int trs[128];
int fail[maxn],num[maxn],in[maxn];
char t[maxm][103];
int n,m;
int tot=0;
inline void fr(int j){
    char c=getchar();
    while(c!='N'&&c!='E'&&c!='W'&&c!='S')c=getchar();
    for(int i=0;;i++){
        if(c=='N'){
            t[j][i]='N';
            c=getchar();
            continue;
        }
        if(c=='E'){
            t[j][i]='E';
            c=getchar();
            continue;
        }
        if(c=='W'){
            t[j][i]='W';
            c=getchar();
            continue;
        }
        if(c=='S'){
            t[j][i]='S';
            c=getchar();
            continue;
        }
        break;
    }
    return;
}
void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return;
}
void ins(char *s,int o){
	int p=0;
	char a;
	for(int i=0;;i++){
		a=s[i];
		if(a=='\0')break;
		if(!ch[p][trs[a]])ch[p][trs[a]]=++tot;
		p=ch[p][trs[a]];
	}
	cnt[p]=1;
	//jump[o]=p;
}
void acam(){
	int p=0;
	queue<int> q;
	for(int i=0;i<4;i++){
		if(ch[0][i])q.push(ch[0][i]);
	}
	while(!q.empty()){
		p=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			if(ch[p][i]){
				fail[ch[p][i]]=ch[fail[p]][i];
				in[ch[fail[p]][i]]++;
				q.push(ch[p][i]);
			}
			else ch[p][i]=ch[fail[p]][i];
		}
	}
}
void query(string &s){
	int p=0;
	char c;
	for(int i=0;i<s.size();i++){
		c=s[i];
		//write(trs[c]);
		p=ch[p][trs[c]]; 
		++num[p];
	}
}
int dfs(char *s){
	int p=0,last=0,depth=0;
	char a;
	for(int i=0;;i++){
		a=s[i];
		//putchar(a);
		if(a=='\0')break;
		p=ch[p][trs[a]];
		depth++;
		if(num[p]>0)last=max(last,depth);		
	}
	return last;
}
int main(){
	//ios::sync_with_stdio(false);
	//freopen("1.txt","r",stdin);	
	trs['N']=0;
	trs['E']=1;
	trs['W']=2;
	trs['S']=3;
	cin>>n>>m;
    cin>>s;
    //cout<<"1"<<endl;
	for(int i=0;i<m;i++){
		fr(i);
		ins(t[i],i);
		//cout<<i<<endl;
	}
	acam();
	query(s);
	queue<int> q;
	for(int i=1;i<=tot;i++){
		if(!in[i])q.push(i);
	}
	while(!q.empty()){
		int p=q.front();q.pop();
		num[fail[p]]+=num[p];
		in[fail[p]]--;
		if(!in[fail[p]])q.push(fail[p]);
	}
	
	for(int i=0;i<m;i++){
		write(dfs(t[i]));
		putchar('\n');
	}
	fclose(stdin);
	return 0;
}
