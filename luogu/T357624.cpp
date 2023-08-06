#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<vector>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int MAXN=2e5;

std::string s;
	int tot=0,rt=0;
	int fa[MAXN],ch[MAXN][2],siz[MAXN];
	char val[MAXN];
    bool tag[MAXN];
	inline void upsiz(int x){siz[x]=1+siz[ch[x][0]]+siz[ch[x][1]];}
	inline bool chk(int x){return x==ch[fa[x]][1];}
	inline void clean(int x){fa[x]=ch[x][0]=ch[x][1]=siz[x]=0;val[x]='0';}
    void pushdown(int x){
        if(tag[x]){
            if(ch[x][0]){
                std::swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
                tag[ch[x][0]]^=1;
            }
            if(ch[x][1]){
                std::swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
                tag[ch[x][1]]^=1;
            }
            tag[x]=0;
        }
    }
	void spin(int x){
		int f=fa[x],dir=chk(x),ff=fa[f];
		fa[ch[x][dir^1]]=f,ch[f][dir]=ch[x][dir^1];
		if(ff)ch[ff][chk(f)]=x;
		fa[f]=x,ch[x][dir^1]=f,fa[x]=ff;
		upsiz(f),upsiz(x);
	}
    void reverse_pushdown(int x){
        if(fa[x])reverse_pushdown(fa[x]);
        pushdown(x);
    }
	void splay(int x,int goal=0){
        reverse_pushdown(x);
		int f=fa[x];
		while((f!=0)&&(f!=goal)){
			if((fa[f]!=0)&&(fa[f]!=goal))spin((chk(x)==chk(f))?f:x);
			spin(x);
			f=fa[x];
		}
		if(goal==0)rt=x;
	}
	int build(int cl,int cr,int f){
        int mid=(cl+cr)/2;
        int cur=++tot;
        if(f==0)rt=cur;
        fa[cur]=f;
        val[cur]=s[mid];
        tag[cur]=0;
        if(cl<=mid-1)ch[cur][0]=build(cl,mid-1,cur);
        if(mid+1<=cr)ch[cur][1]=build(mid+1,cr,cur);
        upsiz(cur);
        return cur;
    }

    int kth(int k){
        int cur=rt;
        while(1){
            pushdown(cur);
            if(k<=siz[ch[cur][0]])cur=ch[cur][0];
            else{
                k-=siz[ch[cur][0]]+1;
                if(k<=0){
                    return cur;
                }
                cur=ch[cur][1];
            }
        }
    }
    void reverse(int l,int r){
        l=kth(l-1);
        r=kth(r+1);
        
        splay(l);
        
        splay(r,l);
        int cur=ch[ch[rt][1]][0];
        std::swap(ch[cur][0],ch[cur][1]);
        tag[cur]^=1;
    }
    void dfs(int x){
        pushdown(x);
        if(ch[x][0])dfs(ch[x][0]);
        if(val[x]!='0'){
            cout<<val[x];
        }
        if(ch[x][1])dfs(ch[x][1]);
    }
int m;
std::vector<std::pair<int,int > > que;
std::string t;
int delta[(int)1e7+10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();  
    cin>>t;
    if(0){
        s.push_back('0');
        s+=t;
        s.push_back('0');
        build(0,s.size()-1,0);
        cin>>m;
    {
        int l,r;
        for(int i{1};i<=m;i++){
            cin>>l>>r;
            l+=1;r+=1;
            if(r<l)std::swap(l,r);
            que.push_back(std::make_pair(l,r));
        }
    }
        for(auto a{que.rbegin()};a!=que.rend();a++){
            reverse((*a).first,(*a).second);
        }
        dfs(rt);

    }
    else{
        cin>>m;
    {
        int l,r;
        for(int i{1};i<=m;i++){
            cin>>l>>r;
            l-=1;r-=1;
            que.push_back(std::make_pair(l,r));
        }
    }
        for(auto a{que.rbegin()};a!=que.rend();a++){
            delta[(*a).first]+=1;delta[(*a).second+1]-=1;
        }
        if(delta[0]%2==1){
            cout<<t[t.size()-1];
        }
        else{
            cout<<t[0];
        }
        for(int i{1};i<t.size();i++){
            delta[i]+=delta[i-1];
            if(delta[i]%2==1){
                cout<<t[t.size()-1-i];
            }
            else{
                cout<<t[i];
            }
        }
    }
    cout<<"\n";
    cout.flush();
    return 0;
}
