# OI 踩坑指南

1. 必须保证自己定义的每一个函数都被调用，尤其是初始化函数。
2. 确定是否需要开 `long long`。
3. 两个 `int` 得到 `long long`。
```cpp
   long long c=1ll*a*b;
   long long c=0ll+a+b;
```
   模意义下的减法请先加模数再取模。

#define int long long
signed main
1ll*a*b%c
(a-b+c)%c
3放放放放放放放放
freopen
freopen
ios::sync_with_stdio(false);

1. 取 `min` 时，要把变量初始化为 `0x3f3f3f3f` 或者其他很大的数值，还要考虑加法或者乘法会不会爆 `long long`。刘汝佳的紫书上提供了另一种方法：每次取 `min` 时，判断一下变量有没有初始化（也就是是不是 `0x3f3f3f3f`），这样可以比较好地应对溢出问题。

2. 先 `freopen`再关同步。
3. 关闭同步后读入一个字符用 `cin.get` 和 `cout.put`。
4. 读入一整行用 `std::getline(cin, str);`，其中 `str` 是 C++ 字符串。
5. 头文件位置：`/lib/gcc/.../.../include/c++`。
6. $a^b \equiv (a \bmod p)^b \not\equiv a^{b\ \bmod\ p} \pmod p$。指数不能取模。
7.  `freopen` 的使用方法：`freopen("airport.in", "r", stdin); freopen("airport.out", "w", stdout);`，在结尾 `fclose(stdin); fclose(stdout);`。  
8.  用`fill`函数给一维赋值：
```cpp
int num[maxn];  
fill(num,num+maxn,-1);
```  
或者`fill(num,num+n,-1);`指定数组长度赋值  
用fill给二维数组赋值：  
```cpp
int num[maxn][maxn];  
fill(num[0][0],num[0][0]+maxn*maxn,-1);  
//值得注意的是，给二维数组赋值时，首地址必须写num[0]。
```  

1.  拷贝`std::copy(start, end, std::back_inserter(container));`
2.  确保数组开的足够大不会溢出，但也不要mle
3.  容器初始化时可以先`.resize()`,否则谨慎使用下标访问
4.  在noilinux上编译
```
g++ name.cpp -Wall -Wextra -std=c++14 -O2 -fsanitize=address,undefined -Wl,--stack=536870912 -g -o name  
g++ name.cpp -Wall -Wextra -std=c++14 -O2 -Wl,--stack=536870912 -g -o name
```  
1.  保留小数点后两位
```cpp
	#include <iomanip> //不要忘了头文件
	cout<<fixed<<setprecision(2);
```

1.  一定要在最后调用 `cout.flush()`。

2.  multiset.count的复杂度是Logarithmic in the size of the container plus linear in the number of elements found.