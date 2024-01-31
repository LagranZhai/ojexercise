#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
std::string s;
struct Node{
    int pos,v;
};
std::vector<Node> st;
int main(){
    ios::sync_with_stdio(false);
    cin>>s;
    for(int i{0};i<s.size();i++){
        if(!st.empty()){
            if(st.back().v==(s[i]-'0')^1){
                st.pop_back();
            }
            else{
                st.push_back({i+1,(s[i]-'0')});
            }
        }
        else{
            st.push_back({i+1,(s[i]-'0')});
        }
    }
    int b{0},gap{0};
    for(Node i:st){
        gap=std::max(gap,i.pos-b-1);
        b=i.pos;
    }
    int l=s.size();
    gap=std::max(gap,l-b);
    cout<<gap<<std::endl;
    cout<<std::flush;
    return 0;
}