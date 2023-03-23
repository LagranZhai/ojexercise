#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=100;
ll a[maxn];
ll n,m,b;
ll minus1_pow(ll a){
    if(a%2==0){
        return 1;
    }
    else{
        return -1;
    }
}
ll piamodp(ll p){
    ll ans=1;
    for(int i=1;i<=n;i++){
        ans=ans*a[i]%p;
    }
    return ans;
}
ll qpow(ll a,ll b){
    ll ans=1;
    while(b>0){
        if(b&1)ans*=a;
        b>>=1;
        a*=a;
    }
    return ans;
}
ll qpow(ll a,ll b,ll M){
    ll ans=1;
    while(b>0){
        if(b&1)ans=ans*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ans;
}
ll ee(ll &a){
	ll e=0; 
	while(a%2==0){
		a=a/2;
		e++;
	}
	return e;
}
ll L_FAST(ll a,ll p) {
	ll s;
	if(a==0){
		return 0;
	}else if(a==1){
		return 1;
	}else{
		if(ee(a)%2==0){
			s=1;
		}else{
			if(p%8==1||p%8==7){
				s=1;
			}
			if(p%8==3||p%8==5){
				s=-1;
			}
		}
		if(p%4==3&&a%4==3){
			s=-s;
		}
		ll p1=p%a;
		if(a==1){
			return s;
		}else{
			return s*L_FAST(p1,a);
		}
	}
}
ll MprimeNodd(ll p,ll b){
    ll N=0;
    N+=qpow(p,n-1);
    ll l=L_FAST(minus1_pow((n-1)/2)*piamodp(p)*b,p);
    N+=l*qpow(p,(n-1)/2);
    return N;
}
ll MprimeNevenBis0(ll p,ll b){
    ll N;
    N=qpow(p,n-1);
    ll l=L_FAST(minus1_pow(n/2)*piamodp(p),p);
    N+=l*(p-1)*qpow(p,n/2-1);
    return N;
}
ll MprimeNevenBisnot0(ll p,ll b){
    ll N;
    N=qpow(p,n-1);
    ll l=L_FAST(minus1_pow(n/2)*piamodp(p),p);
    N-=l*qpow(p,n/2-1);
    return N;
}
ll Mprime(ll p,ll b){
    ll ans;
    if(n%2==1){
        ans=MprimeNodd(p,b);
    }
    else{
        if(b==0){
            ans=MprimeNevenBis0(p,b);
        }
        else{
            ans=MprimeNevenBisnot0(p,b);
        }
    }
    return ans;
}
ll MisnotprimeBis0(ll p,ll k){
    ll v=(qpow(p,k*(n-1)-1)-qpow(p,(n-1)*(k-1)-(n-2)*((k+1)/2-1)))
        /(qpow(p,n-2)-1)*(Mprime(p,0)-1)+qpow(p,n*k/2);
    return v;
}
ll MisnotprimeBisnot0(ll p,ll k,ll s){
    if(s%2==1){
        ll v=(qpow(p,k*(n-1)-1)-qpow(p,(n-1)*(k-1)-(n-2)*(s-1)/2))
            /(qpow(p,n-2)-1)*(Mprime(p,0)-1);
        return v;
    }
    else{
        ll v=(qpow(p,k*(n-1)-1)-qpow(p,(n-1)*(k-1)-(n-2)*(s-2)/2))
            /(qpow(p,n-2)-1)*(Mprime(p,0)-1)+qpow(p,(n-1)*(k-1)-(n-1)/2*s)*Mprime(p,b/qpow(p,s));
        return v;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>b;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        //pia*=a[i];//pia < ll needed
    }
    
    return 0;
}