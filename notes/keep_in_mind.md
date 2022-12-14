# OI 踩坑指南

1. 必须保证自己定义的每一个函数都被调用，尤其是初始化函数。
2. 确定是否需要开 `long long`。
3. 两个 `int` 得到 `long long`。
```cpp
   long long c=1ll*a*b;
   long long c=0ll+a+b;
```

4. 取 `min` 时，要把变量初始化为 `0x3f3f3f3f` 或者其他很大的数值，还要考虑加法或者乘法会不会爆 `long long`。刘汝佳的紫书上提供了另一种方法：每次取 `min` 时，判断一下变量有没有初始化（也就是是不是 `0x3f3f3f3f`），这样可以比较好地应对溢出问题。

5. 先关闭同步再用 `freopen`。
6. 关闭同步后读入一个字符用 `cin.get` 和 `cout.put`。
7. 读入一整行用 `std::getline(cin, str);`，其中 `str` 是 C++ 字符串。
8. 头文件位置：`/lib/gcc/.../.../include/c++`。
9. $a^b \equiv (a \bmod p)^b \not\equiv a^{b\ \bmod\ p} \pmod p$。指数不能取模。
10. `freopen` 的使用方法：`freopen("airport.in", "r", stdin); freopen("airport.out", "w", stdout);`，在结尾 `fclose(stdin); fclose(stdout);`。
