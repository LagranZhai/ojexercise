# OI 踩坑指南

1. 必须保证自己定义的每一个函数都被调用，尤其是初始化函数。
2. 确定是否需要开 `long long`。
3. 两个 `int` 得到 `long long`。
```cpp
   long long c=1ll*a*b;
   long long c=0ll+a+b;
```

4. 取 `min` 时，要把变量初始化为 `0x3f3f3f3f` 或者其他很大的数值，还要考虑加法或者乘法会不会爆 `long long`。刘汝佳的紫书上提供了另一种方法：每次取 `min` 时，判断一下变量有没有初始化（也就是是不是 `0x3f3f3f3f`），这样可以比较好地应对溢出问题。

5. 先 `freopen`再关同步。
6. 关闭同步后读入一个字符用 `cin.get` 和 `cout.put`。
7. 读入一整行用 `std::getline(cin, str);`，其中 `str` 是 C++ 字符串。
8. 头文件位置：`/lib/gcc/.../.../include/c++`。
9. $a^b \equiv (a \bmod p)^b \not\equiv a^{b\ \bmod\ p} \pmod p$。指数不能取模。
10. `freopen` 的使用方法：`freopen("airport.in", "r", stdin); freopen("airport.out", "w", stdout);`，在结尾 `fclose(stdin); fclose(stdout);`。  
11. 用`fill`函数给一维赋值：
```cpp
int num[maxn];  
fill(num,num+maxn,-1);
```  
或者`fill(num,num+n,-1);`指定数组长度赋值  
用fill给二维数组赋值：  
```cpp
int num[maxn][maxn];  
fill(num[0],num[0]+maxn*maxn,-1);  
//值得注意的是，给二维数组赋值时，首地址必须写num[0]。
```  

11. 拷贝`std::copy(start, end, std::back_inserter(container));`
12. 确保数组开的足够大不会溢出，但也不要mle
13. 容器初始化时可以先`.resize()`,否则谨慎使用下标访问
14. 在noilinux上编译
```
g++ name.cpp -Wall -Wextra -std=c++14 -O2 -fsanitize=address,undefined -Wl,--stack=536870912 -g -o name  
g++ name.cpp -Wall -Wextra -std=c++14 -O2 -Wl,--stack=536870912 -g -o name
```  
15. 保留小数点后两位
```cpp
	#include <iomanip> //不要忘了头文件
	cout<<fixed<<setprecision(2);
```

16. 一定要在最后调用 `cout.flush()`。
