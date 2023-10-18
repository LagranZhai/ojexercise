#include <iostream>

using namespace std;

const int MAXN = 1e5 + 7;


	int rt, tot;
	struct Node {
		int fa, ch[2], val, cnt, sz;
		Node () {}
		Node (int fa, int ch1, int ch2, int val, int cnt) : 
			fa(fa), ch{ch1, ch2}, val(val), cnt(cnt) {} 
	} t[MAXN];
	void maintain(int x) {
		t[x].sz = t[t[x].ch[0]].sz + t[t[x].ch[1]].sz + t[x].cnt;
	}
	bool get(int x) {
		return x == t[t[x].fa].ch[1];
	}
	void clear(int x) {
		t[x].ch[0] = t[x].ch[1] = t[x].fa = t[x].val = t[x].cnt = t[x].sz = 0;
	}
	
	void rotate(int x) {
		int y = t[x].fa, z = t[y].fa, xson = get(x), yson = get(y);
		t[y].ch[xson] = t[x].ch[xson ^ 1];
		if (t[x].ch[xson ^ 1]) t[t[x].ch[xson ^ 1]].fa = y;
		
		t[x].ch[xson ^ 1] = y;
		t[y].fa = x; t[x].fa = z;
		if (z) t[z].ch[yson] = x;
		
	 	maintain(y); maintain(x);
	}
	
	void splay(int x) {
		for (int f = t[x].fa; f = t[x].fa, f; rotate(x)) 
			if (t[f].fa) rotate(get(x) == get(f) ? f : x);
		rt = x; 
	}	
int main(){
	auto ins=[&](int k, int cur, int fa, auto&& self) {
		if (!cur) {
			if (!rt) {
				t[++ tot] = Node{0, 0, 0, k, 1};
				rt = tot; maintain(rt);	
			} else {
				t[++ tot] = Node{fa, 0, 0, k, 1};
				t[fa].ch[t[fa].val < k] = tot;
				maintain(tot); maintain(fa);
				splay(tot);
			}
			return ;
		}
		if (t[cur].val == k) {
			t[cur].cnt ++; 
			maintain(cur); maintain(fa);
			splay(cur);
			return ;
		}
		self(k, t[cur].ch[t[cur].val < k], cur, self);
	};
	auto rk=[&](int k, int cur, auto&& self)->int {
		if (k < t[cur].val) return self(k, t[cur].ch[0], self);
		if (k == t[cur].val) { splay(cur); return t[t[cur].ch[0]].sz + 1; }
		return self(k, t[cur].ch[1], self);
	};
	auto kth=[&](int k, int cur, auto&& self)->int {
		if (t[cur].ch[0] && k <= t[t[cur].ch[0]].sz) return self(k, t[cur].ch[0], self);
		if (k > t[cur].cnt + t[t[cur].ch[0]].sz) return self(k - t[cur].cnt - t[t[cur].ch[0]].sz, t[cur].ch[1], self);
		splay(cur);
		return t[cur].val;
	};
	auto pre=[&]() {
		int cur = t[rt].ch[0];
		if (! cur) return cur;//不能直接返回，del有问题
		while (t[cur].ch[1]) cur = t[cur].ch[1];
		splay(cur);
		return cur;
	};
	auto nxt=[&]() {
		int cur = t[rt].ch[1];
		if (! cur) return cur;
		while (t[cur].ch[0]) cur = t[cur].ch[0];
		splay(cur);
		return cur;
	};
	auto del=[&](int x) {
		rk(x, rt, rk);
		if (t[rt].cnt > 1) {
			t[rt].cnt --;
			maintain(rt);
			return ;
		}
		if (!t[rt].ch[0] && !t[rt].ch[1]) {
			clear(rt); rt = 0;
			return ;
		}
		if (!t[rt].ch[0]) {
			int cur = rt; 
			rt = t[rt].ch[1];
			t[rt].fa = 0;
			clear(cur);
			return ;
		}
		if (!t[rt].ch[1]) {
			int cur = rt; 
			rt = t[rt].ch[0];
			t[rt].fa = 0;
			clear(cur);
			return ;
		}
		int cur = rt, l = pre();//合并
		t[t[cur].ch[1]].fa = l;
		t[l].ch[1] = t[cur].ch[1];
		clear(cur);
		maintain(rt);
	};


int T;


	cin >> T;
	while (T --) {
		int op, x; cin >> op >> x;
		if (op == 1) ins(x, rt, 0, ins);
		if (op == 2) del(x);
		if (op == 3) cout << rk(x, rt, rk) << '\n';
		if (op == 4) cout << kth(x, rt, kth) << '\n';
		if (op == 5) ins(x, rt, 0, ins), cout << t[pre()].val << '\n', del(x);
		if (op == 6) ins(x, rt, 0, ins), cout << t[nxt()].val << '\n', del(x);
	}
	return 0;
}
