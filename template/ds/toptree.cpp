#include<bits/stdc++.h>
using std::cin,std::cout;
namespace TopTree{
    template<typename Dtype,typename Ttype>
    struct TopTree{
        struct Node{
            int ls,rs,ms;
            int fa;
            int siz;
            bool rev;
            Dtype d;
            Ttype t;
        };
        int tot{};
        std::vector<Node> tree;
        std::stack<int> node_pool;
        int new_node(){
            if(!node_pool.empty()){
                int t{node_pool.top()};
                node_pool.pop();
                return t;
            }
            return ++tot;
        }
        template<bool type>
        void pushdown<false>(){
            
        }
        void pushup(){

        }
        void rotate(){

        }
        void splay(){

        }
        void access(){

        }
        void splice(){

        }
        void makeroot(){

        }
        void link(){

        }
        void cut(){
            
        }
    };

    
}