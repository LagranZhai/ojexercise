n=int(input())
p=[]
for i in range(1, n+1):
    p.append(float(input()))
t=[p[0]]
s=[p[n-1]]
ans=p[n-1]+p[n-2]
for i in range(0, n-2):
    t.append(p[i+1]*(t[i]+1))
    s.append(p[n-2-i]*(s[i]+1))
    ans+=p[i]
for i in range(0, n-1):
    ans+=6*t[i]*s[n-2-i]
print(round(ans,1))