#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
int a[maxn+100];
int dp[maxn];
int main(){
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
            for(int l{1};i+l-1<n;l++){
                g=std::__gcd(g,a[(i+l-1)*m+j]);
                ans+=g;
                if(g==1){
                    ans+=(n-(i+l-1))*(m-j)-1;
                    break;
                }
                else{
                    dp[j]=g;
                    if(l==1){
                        for(int w{2};j+w-1<m;w++){
                            dp[j+w-1]=std::__gcd(dp[j+w-2],a[(i+l-1)*m+j+w-1]);
                            if(dp[j+w-1]==1){
                                ans+=m-(j+w-1);
                                break;
                            }
                            else{
                                ans+=dp[j+w-1];
                            }
                        }
                    }
                    else{
                        for(int w{2};j+w-1<n;w++){
                            dp[j+w-1]=std::__gcd(std::__gcd(dp[j+w-1],dp[j+w-2]),a[(i+l-1)*m+j+w-1]);
                            if(dp[j+w-1]==1){
                                ans+=m-(j+w-1);
                                break;
                            }
                            else{
                                ans+=dp[j+w-1];
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