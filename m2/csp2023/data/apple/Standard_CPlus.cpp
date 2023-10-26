#include <bits/stdc++.h>
using namespace std;

int N, K, L, t;
int parent[50000];
int length[50000];
vector<vector<int> > tree;
vector<vector<int> > res;
vector<vector<int> > tmp;
int main()
{
    cin >> N >> K;
    tree.resize(N); tmp.resize(N); res.resize(N);
    for(int i = 1; i < N; ++i) {
        scanf("%d", &t);
        tree[t].push_back(i);
        tree[i].push_back(t);
    }
    vector<int> st;
    st.push_back(K);
    parent[K] = K;
    length[K] = 0;
    for(; !st.empty(); ) {
        t = st.back();
        st.pop_back();
        for(int i = 0; i < tree[t].size(); ++i) {
            if(tree[t][i] != parent[t]) {
                parent[tree[t][i]] = t;
                length[tree[t][i]] = length[t] + 1;
                st.push_back(tree[t][i]);
            }
        }
    }
    for(int i = 0; i < N; ++i) {
        if(tree[i].size() == 1) {
            res[length[i]].push_back(i);
        }
    }
    for(int i = N - 1; i > 0; --i) {
        for(int j = 0; j < res[i].size(); ++j) {
            int len = 0;
            int cur = res[i][j];
            for(; length[cur] != 0; ++len) {
                length[cur] = 0;
                cur = parent[cur];
            }
            length[res[i][j]] = len;
        }
        res[i].clear();
    }
    for(int i = 0; i < N; ++i) {
        if(tree[i].size() == 1) {
            res[length[i]].push_back(i);
        }
    }
    printf("%d\n", K);
    for(int i = N - 1; i > 0; --i) {
        for(int j = 0; j < res[i].size(); ++j) {
            printf("%d\n", res[i][j]);
        }
    }
 	return 0;
}