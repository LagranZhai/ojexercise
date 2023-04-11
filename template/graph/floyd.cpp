for(int k=1;k<=n;i++){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=max(dp[i][j],dp[i][k]+dp[k][j]);
        }
    }
}
