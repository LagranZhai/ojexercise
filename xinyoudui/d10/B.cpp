    const int maxn=5e3,p=1e9+7;
    int S[maxn][maxn];    
    int f[maxn]{},g[maxn]{};
class CountTables{
public:
    int qpow(int a,int b){
        int c{1};
        while(b){
            if(b&1)c=1ll*c*a%p;
            a=1ll*a*a%p;
            b>>=1;
        }
        return c;
    }
    int n,m,c;
    signed howMany(signed N, signed M, signed C){
        n=N;m=M;c=C;
        S[0][0]=1;
        for(int i{1};i<=m;i++){
            S[i][0]=0;
            for(int j{1};j<=i;j++){
                S[i][j]=(1ll*(i-1)*S[i-1][j]%p+S[i-1][j-1])%p;
            }
        }
        int base{1};
        for(int i{1};i<=m;i++){
            f[i]=1;base=1ll*base*m%p;
            for(int j{};j<n;j++){
                f[i]=1ll*f[i]*((0ll+base-j+p)%p)%p;
            }
        }
        for(int i{1};i<=m;i++){
            bool flag{m%2ll==1};
            for(int j{0};j<=m;j++){
                g[i]=(0ll+g[i]+(1ll*(flag?-1:1)*S[m][j]*f[j]+p)%p)%p;
                flag^=1;
            }
        }
        return g[m];
    }
};
