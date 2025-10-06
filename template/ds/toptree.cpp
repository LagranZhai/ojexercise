#include<bits/stdc++.h>
using std::cin,std::cout;
namespace TopTree{
    constexpr bool compress{false},rake{true};
    constexpr int maxn=1;
    // template<typename Dtype,typename Ttype>
    struct TopTree{
        struct Node{
            int v;
            int sum;
            // int chaintag,subtreetag;
            // int chainsum,subtreesum;
            // Dtype d;
            // Ttype t;
        };
        std::vector<std::array<int,3>> ch;
        // int ls[maxn],rs[maxn],ms[maxn];
        std::vector<int> fa;
        std::vector<int> siz;
        std::vector<int> rev;
        int tot{};
        std::vector<Node> tree;
        std::stack<int> node_pool;
        int& ls(const int i){return ch[i][0];}
        int& rs(const int i){return ch[i][1];}
        int& ms(const int i){return ch[i][2];}
        int new_node(){
            if(!node_pool.empty()){
                int t{node_pool.top()};
                node_pool.pop();
                return t;
            }
            ++tot;
            ch.resize(tot+10);fa.resize(tot+10);siz.resize(tot+10);rev.resize(tot+10);tree.resize(tot+10);
            return tot;
        }
        template<bool type>
        void pushup(int x){
            if constexpr(type==compress){
                // x.siz=rs(x).siz+ms(x).siz+1;
                siz[x]=siz[rs(x)]+siz[ms(x)]+1;
                tree[x].sum=tree[ls(x)].sum^tree[rs(x)].sum^tree[x].v;
            }
            else{
                // x.siz=ls(x).siz+rs(x).siz+ms(x).siz;
                siz[x]=siz[ls(x)]+siz[rs(x)]+siz[ms(x)];
            }
        }
        void applyrev(int x){
            std::swap(ls(x),rs(x));
            rev[x]^=1;
        }
        template<bool type>
        void pushdown(int x){
            if constexpr(type==compress){
                if(rev[x]){
                    applyrev(ls(x));
                    applyrev(rs(x));
                    rev[x]=0;
                }
            }
        }
        int chk(int x){
            if(ls(fa[x])==x)return 1;
            if(rs(fa[x])==x)return 0;
            return -1;
        }
        template<bool type>
        void rotate(int x){
            int f=fa[x],dir=chk(x),ff=fa[f];
            if(chk(f)!=-1)ch[ff][chk(f)]=x;
            fa[ch[x][dir^1]]=f;ch[f][dir]=ch[x][dir^1];
            fa[f]=x;ch[x][dir^1]=f;fa[x]=ff;
            pushup<type>(f);pushup<type>(x);
        }
        template<bool type>
        void pushdownfromroot(int x){
            if(chk(x)!=-1)pushdownfromroot<type>(fa[x]);
            pushdown<type>(x);
        }
        template<bool type>
        void splay(int x,int d=0){
            pushdownfromroot<type>(x);
            int f=fa[x];
            while(chk(x)!=-1&&f!=d){
                if(chk(f)!=-1&&fa[f]!=d)rotate<type>(chk(f)==chk(x)?f:x);
                rotate<type>(x);
                f=fa[x];
            }
        }
        void setfather(int x,int f,int dir){
            if(f)ch[f][dir]=x;
            if(x)fa[x]=f;
        }
        void clear(int x){
            ch[x][0]=ch[x][1]=ch[x][2]=fa[x]=siz[x]=rev[x]=0;
            tree[x]=Node();
            node_pool.push(x);
        }
        void del(int x){
            setfather(ms(x),fa[x],1);
            if(ls(x)){
                int p{ls(x)};
                while(true){
                    pushdown<rake>(p);
                    if(!rs(p))break;
                    p=rs(p);
                }
                splay<rake>(p,x);
                setfather(rs(x),p,1);
                setfather(p,fa[x],2);
                pushup<rake>(p);
                pushup<compress>(fa[p]);
            }
            else{
                setfather(rs(x),fa[x],2);
                pushup<compress>(fa[x]);
            }
            clear(x);
        }
        void splice(int x){
            int f{fa[x]},ff{fa[f]};
            if(rs(ff)){
                std::swap(fa[rs(ff)],fa[x]);
                std::swap(rs(ff),ms(f));
            }
            else{
                del(f);
            }
            if(ms(ff))pushup<rake>(ms(ff));
            pushup<compress>(ff);
        }
        void access(int x){
            splay<compress>(x);
            if(rs(x)){
                int now{new_node()};
                setfather(ms(x),now,0);
                setfather(rs(x),now,2);
                rs(x)=0;
                setfather(now,x,2);
                pushup<rake>(now);
                pushup<compress>(x);
            }
            int f=fa[x];
            while(true){
                splay<compress>(x);
                f=fa[x];
                if(!f)break;
                splay<rake>(f);
                int ff=fa[f];
                splay<compress>(ff);
                pushdown<rake>(f);
                pushdown<compress>(x);
                splice(x);
            }
        }
        void makeroot(int x){
            access(x);
            applyrev(x);
        }
        void expose(int x,int y){
            makeroot(x);
            access(y);
        }
        int findroot(int x){
            access(x);
            while(true){
                pushdown<compress>(x);
                if(!ls(x))break;
                x=ls(x);
            }
            splay<compress>(x);
            return x;
        }
        void link(int x,int y){
            if(findroot(x)==findroot(y)){
                return ;
            }
            access(x);
            makeroot(y);
            setfather(y,x,1);
            pushup<compress>(x);
        }
        void cut(int x,int y){
            expose(x,y);
            if(ls(y)!=x||rs(x))return;
            fa[x]=ls(y)=0;
            pushup<compress>(y);
        }
    };

}