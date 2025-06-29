int det(int n){
    int ans=1,op=0;
    for(int i{1};i<=n;i++){
        for(int j{i+1};j<=n;j++){
            int x{i},y{j};
            while(c[y][i]){
                int t=c[x][i]/c[y][i];
                for(int k{i};k<=n;k++)c[x][k]=(0ll+c[x][k]-1ll*c[y][k]*t%p)%p;
                std::swap(x,y);
            }
            if(x!=i){
                // std::swap(c[i],c[x]);
                for(int k{1};k<=n;k++){
                    std::swap(c[x][k],c[i][k]);
                }
                op^=1;
            }
        }
        if(c[i][i]==0)return 0;
        else ans=1ll*ans*c[i][i]%p;
    }
    if(op)ans=-ans;
    return (0ll+ans+p)%p;
}