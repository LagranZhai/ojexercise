#include<bits/stdc++.h>
using namespace std;
using i64=long long;
const int N = 1e5 + 5, P = 998244353;
const i64 inf = 1e14;

struct vec1
{
	i64 a, b, z;
}tr[N << 2];
struct vec2
{
	i64 a0, a1, a2, a3;
	inline void init()
	{
		a0 = 0;
		a1 = a2 = a3 = -inf;
	}
}tag[N << 2], add, chg, fre;
bool have[N << 2];

inline vec1 operator + (const vec1 x, const vec1 y)
{
	vec1 res; 
	res.a = max(x.a, y.a);
	res.b = max(x.b, y.b);
	res.z = 0;
	return res;
}
inline vec1 operator * (const vec2 x, const vec1 y)
{
	vec1 res;
	res.a = max(x.a0 + y.a, x.a1);
	res.b = max(x.a2 + y.a, max(y.b, x.a3));
	res.z = 0;
	return res;
}
inline vec2 operator * (const vec2 x, const vec2 y)
{
	vec2 res;
	res.a0 = x.a0 + y.a0;
	res.a1 = max(x.a0 + y.a1, x.a1);
	res.a2 = max(x.a2 + y.a0, y.a2);
	res.a3 = max(x.a2 + y.a1, max(y.a3, x.a3));
	return res;
}
inline void built(int p, int l, int r)
{
	tag[p].init();
	if (l == r)
	{
		cin >> tr[p].a, tr[p].b = tr[p].a;
		return;
	}
	int mid = l + r >> 1;
	built(p << 1, l, mid);
	built(p << 1 | 1, mid + 1, r);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
inline void pushdown(int p)
{
	if (!have[p]) return;
	tr[p << 1] = tag[p] * tr[p << 1], tag[p << 1] = tag[p] * tag[p << 1], have[p << 1] = 1;
	tr[p << 1 | 1] = tag[p] * tr[p << 1 | 1], tag[p << 1 | 1] = tag[p] * tag[p << 1 | 1], have[p << 1 | 1] = 1;
	have[p] = 0, tag[p].init();
}
inline void update(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return tr[p] = add * tr[p], tag[p] = add * tag[p], have[p] = 1, void();
	pushdown(p);
	int mid = l + r >> 1;
	if (L <= mid) update(p << 1, l, mid, L, R);
	if (mid < R) update(p << 1 | 1, mid + 1, r, L, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
inline void change(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return tr[p] = chg * tr[p], tag[p] = chg * tag[p], have[p] = 1, void();
	pushdown(p);
	int mid = l + r >> 1;
	if (L <= mid) change(p << 1, l, mid, L, R);
	if (mid < R) change(p << 1 | 1, mid + 1, r, L, R);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}
inline i64 ask0(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return tr[p].a;
	pushdown(p);
	int mid = l + r >> 1; i64 res = -inf;
	if (L <= mid) res = max(res, ask0(p << 1, l, mid, L, R));
	if (mid < R) res = max(res, ask0(p << 1 | 1, mid + 1, r, L, R));
	return res;
}
inline i64 ask1(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return tr[p].b;
	pushdown(p);
	int mid = l + r >> 1; i64 res = -inf;
	if (L <= mid) res = max(res, ask1(p << 1, l, mid, L, R));
	if (mid < R) res = max(res, ask1(p << 1 | 1, mid + 1, r, L, R));
	return res;
}

signed main()
{
    freopen("P4314_1.in","r",stdin);
    // freopen("4314.in","r",stdin);
	freopen("4314.cpp","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;
	built(1, 1, n);
	add.init(), chg.init(), fre.init();
	chg.a0 = -inf, fre.a2 = 0;

	int m; cin >> m;
	for (int i = 1; i <= m; ++i)
	{
		char op; int x, y;
		cin >> op >> x >> y;
		if (op == 'Q') cout << ask0(1, 1, n, x, y) << '\n';
		else if (op == 'A') cout << ask1(1, 1, n, x, y) << '\n';
		else if (op == 'P') cin >> add.a0, update(1, 1, n, x, y);
		else cin >> chg.a1, change(1, 1, n, x, y);
		tr[1] = fre * tr[1], tag[1] = fre * tag[1], have[1] = 1;
	}
	
	return 0;
}