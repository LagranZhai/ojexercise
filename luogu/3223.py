n,m=0,0
n,m=input().split(" ")
n=int(n)
m=int(m)
fac=[0]*3001
fac[0]=1
for i in range(1,3000):
    fac[i]=fac[i-1]*i
ans=0
if n+3>=m:
    ans=fac[n+2]*fac[n+3]//fac[n+3-m]
if n+2>=m:
    ans=ans-2*fac[n+1]*fac[n+2]//fac[n+2-m]
print(int(ans))