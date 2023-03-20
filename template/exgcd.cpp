#include<bits/stdc++.h>
using namespace std;
void exgcd(int &x,int &y,int a,int b){
    if(b==0){
        x=1;y=0;
        return;
    }
    else {exgcd(y,x,b,a%b);y-=(a/b)*x;}
}
int exgcd1(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd1(b, a % b, y, x); //这里交换了x和y
    y -= (a / b) * x;
    return d;
}
int main(){
    ios::sync_with_stdio(false);
    srand(time(0));
    for(int i=1;i<=100;i++){
        int x1,y1,x2,y2;
        int a=rand(),b=rand();
        exgcd(x1,y1,a,b);
        exgcd1(a,b,x2,y2);
        if(x1!=x2||y1!=y2)cout<<'w'<<endl;
    }
    return 0;
}