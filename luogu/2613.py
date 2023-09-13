p=19260817
def qpow(a,b)->int:
    c=1
    while b>0:
        if b&1!=0:
            c=c*a%p
        b=b>>1
        a=a*a%p
    return c
a=int(input())
b=int(input())
if a%p==0&b%p!=0:
    print("Angry!")
else:
    print(a*qpow(b,p-2)%p)
