#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

//#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
//#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

//#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
//#endif

using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e5;
#define int long long
int n;
int a[maxn*2],b[maxn*2];
struct Node{
//	Node()=default;
	//int l{0},r{0},cnt{0};
	int l,r,cnt;
}s[maxn*2];
struct Data{
	int max{0};
	Data operator+(Data A){
		Data res;
		res.max=std::max(max,A.max);
		return res;
	}
}tree[maxn*2];
void query(int p,int cl,int cr,int l,int r,Data &ans){
	if(l>r)return ;
	if(cl>=l&&cr<=r){
		ans=ans+tree[p];
		return ;
	}
	if(cl!=cr){
		int mid=(cl+cr)/2;
		if(mid>=l)query(p*2,cl,mid,l,r,ans);
		if(mid<r)query(p*2+1,mid+1,cr,l,r,ans);
		return ;
	}
}
void update(int p,int cl,int cr,int l,int r,Data d){
	if(l>r)return ;
	if(cl>=l&&cr<=r){
		tree[p]=tree[p]+d;
		return ;
	}
	if(cl!=cr){
		int mid=(cl+cr)/2;
		if(mid>=l)update(p*2,cl,mid,l,r,d);
		if(mid<r)update(p*2+1,mid+1,cr,l,r,d);
		tree[p]=tree[p*2]+tree[p*2+1];
		return ;
	}
}
int dp[maxn*2];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	std::vector<Node> tmp;
	cin>>n;
	for(int i{1};i<=n;i++){
		cin>>a[i]>>b[i];
//		Node cur{b[i]+1,n-a[i],0};
//		cur.cnt=0;cur.l=b[i]+1;cur.r=n-a[i]; 
		if(b[i]+1>n-a[i])continue;
		tmp.push_back({b[i]+1,n-a[i],0});
	}
	std::sort(std::begin(tmp),std::end(tmp),[](const Node &a,const Node &b){
		if(a.l==b.r){
			return a.r<b.r;
		}
		else return a.l<b.l;
	});
	int num{0};
	for(int i{0};i<tmp.size();i++){
		if(tmp[i].l==s[num].l&&tmp[i].r==s[num].r){
			if(s[num].cnt<s[num].r-s[num].l+1){
				s[num].cnt++;
			}
		}
		else{
			s[++num]=tmp[i];
			s[num].cnt++;
		}
	}
	std::sort(s+1,s+num+1,[](const Node &a,const Node &b){
		if(a.r==b.r){
			return a.l<b.l;
		}
		else return a.r<b.r;
	});
//	cout<<"\n";
	for(int i{1};i<=num;i++){
//		cout<<s[i].l<<" "<<s[i].r<<"\n";
		Data ans{};
		query(1,1,n,1,s[i].l-1,ans);
		dp[i]=std::max(dp[i-1],ans.max+s[i].cnt);
		ans.max=dp[i];
		update(1,1,n,s[i].r,s[i].r,ans);
	}
	Data ans{};
//	query(1,1,n,1,n,ans);
	cout<<n-dp[num]<<"\n";
	cout.flush();
	return 0;
}