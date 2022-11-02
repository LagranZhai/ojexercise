#include<iostream>
using namespace std;
const int maxn=3e6+36;
int n,top=0;
int a[maxn],s[maxn],f[maxn];
int fr(){
    int w=0,f=1;
    char c=cin.get();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=cin.get();
    }
    while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
    return w*f;
}
int main(){
    ios::sync_with_stdio(false);
    n=fr();
    for(int i=1;i<=n;i++)a[i]=fr();
    f[0]=0;
    for(int i=n;i>=1;i--){
        while(top>0&&a[i]>=a[s[top]])top--;
        f[i]=s[top];
        s[++top]=i;
    }
    for(int i=1;i<=n;i++){
        cout<<f[i]<<" ";
    }
    return 0;
}
