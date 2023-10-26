#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int dis1[N],dis2[N],num1[N],num2[N],head1[N],head2[N],n,k,cnt1=0,cnt2=0;
stack <int>s;

struct node{
	int to,next;
}e1[N],e2[N];

void add1(int x,int y)
{
	cnt1++;
	e1[cnt1].to=y;
	e1[cnt1].next=head1[x];
	head1[x]=cnt1;
}

void add2(int x,int y)
{
	cnt2++;
	e2[cnt2].to=y;
	e2[cnt2].next=head2[x];
	head2[x]=cnt2;
}

void dfs1(int x)
{
	//cout<<111;
	if(s.empty() )
	{
		return ;
	}
	while(!s.empty())
	{
		int m=s.top();
		s.pop() ;
		//dis1[m]=x;
		for(int i=1;i<x;i++)
		{
			num1[i]++;
			cout<<"num1["<<i<<"]="<<num1[i]<<endl;
		}
		for(int i=head1[m];i!=0;i=e1[i].next)
		{
			s.push(e1[i].to);
			cout<<"e1["<<i<<"].to="<<e1[i].to<<endl; 
		}
	}
	dfs1(x+1);
	return ;
}

void dfs2(int x)
{
	if(s.empty() )
	{
		return ;
	}
	while(!s.empty())
	{
		int m=s.top();
		//cout<<"   m="<<m<<endl;
		s.pop() ;
		//dis2[m]=x;
		for(int i=1;i<x;i++)
		{
			num2[i]++;
			cout<<"num2["<<i<<"]="<<num2[i]<<endl;
		}
		for(int i=head2[m];i!=0;i=e2[i].next)
		{
			s.push(e2[i].to);
			cout<<"e2["<<m<<"].to="<<e2[i].to<<endl; 
		}
	}
	dfs2(x+1);
	return ;
}

int main()
{
	int n;
	cin>>n;
	int x,y;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add1(x,y);
	}
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add2(x,y);
	}
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	s.push(1); 
	dfs1(1);
	
	s.push(1); 
	dfs2(1);
	long long ans=0;
	for(int i=1;i<n;i++)
	{
		ans+=num1[i]*num2[i];
	}
	cout<<ans;
}
