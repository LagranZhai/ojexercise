int det(int n){
//     int res{1};bool op{0};
//     for(int i{1};i<=n;i++){
//         int now{i};
//         for(int j{i};j<=n;j++){
//             if(c[j][i]){
//                 now=j;break;
//             }
//         }
//         if(now!=i){
//             std::swap(c[now],c[i]);op^=1;
//         }
//         int v{qpow(c[i][i],p-2)};
//         for(int j{i+1};j<=n;j++){
//             int div{(-1ll*c[j][i]+p)%p*v%p};
//             for(int k{i};k<=n;k++){
//                 c[j][k]=(c[j][k]+c[i][k]*div%p)%p;
//             }
//             // if(c[j][i]!=1ll)cerr<<"w";
//         }
//     }
//     for(int i{1};i<=n;i++){
//         res=(res*c[i][i])%p;
//     }
//     if(op){
//         return p-res;
//     }
//     else{
//         return res;
//     }
// }