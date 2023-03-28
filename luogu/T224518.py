t=int(input())
ans=[]
while t>0:
    n=int(input())
    l=0
    for i in range(1,n+1):
        opt=[]
        q=[]
        q=input().split(" ")
        for j in range(0,len(q)):
            opt.append(int(q[j]))
        if opt[0]==1:
            l*=2
        if opt[0]==2:
            d=opt[1]
            l+=d
    b=[]
    if l==0:
        ans.append(0)
        t-=1
        continue
    while l>0:
        b.append(l%2)
        l=l//2
    s=""
    for j in range(0,len(b)):
        s+=str(b[len(b)-j-1])
    ans.append(s)
    t-=1
for i in range(0,len(ans)):
    print(ans[i])
