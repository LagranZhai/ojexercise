n=int(input())
sumd=0
fac=[1]
for i in range(1,200):
    fac.append(fac[-1]*i)
res=1
d=input().split(" ")
for i in range(0,n):
    d[i]=int(d[i])
    sumd=sumd+d[i]
    res=res*fac[d[i]-1]
if sumd!=2*n-2:
    print(0)
else:
    if n==1:
        print(1)
    else:
        ans=fac[n-2]//res
        print(ans)

    