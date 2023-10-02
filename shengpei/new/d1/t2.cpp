#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
#define int long long
int a[maxn+100];
int dp[maxn];
signed main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i{0};i<n;i++){
        for(int j{0};j<m;j++){
            cin>>a[i*m+j];
        }
    }
    int aans{0};
    std::fill(dp,dp+1100,1);
    for(int i{0};i<n;i++){
        for(int j{0};j<m;j++){
            int ans=0;
            int g=a[i*m+j];
            for(int l{1};j+l-1<m;l++){
                g=std::__gcd(g,a[i*m+j+l-1]);
                ans+=g;
                if(g==1){
                    ans+=(n-i)*(m-(j+l-1))-1;
                    break;
                }
                else{
                    dp[i]=g;
                    if(l==1){
                        for(int w{2};i+w-1<n;w++){
                            dp[i+w-1]=std::__gcd(dp[i+w-2],a[(i+w-1)*m+j+l-1]);
                            if(dp[i+w-1]==1){
                                ans+=n-(i+w-1);
                                break;
                            }
                            else{
                                ans+=dp[i+w-1];
                            }
                        }
                    }
                    else{
                        for(int w{2};i+w-1<n;w++){
                            dp[i+w-1]=std::__gcd(std::__gcd(dp[i+w-1],dp[i+w-2]),a[(i+w-1)*m+j+l-1]);
                            if(dp[i+w-1]==1){
                                ans+=n-(i+w-1);
                                break;
                            }
                            else{
                                ans+=dp[i+w-1];
                            }
                        }                        
                    }

                }
            }
            // cout<<ans<<" ";
            aans+=ans;
        }
        // cout<<"\n";
    }
    cout<<aans<<std::endl;
    // for(int i{0};i<n;i++){
    //     for(int j{0};j<m;j++){
    //         cout<<a[i*m+j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    return 0;
}