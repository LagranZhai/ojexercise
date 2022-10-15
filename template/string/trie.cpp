#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 3e6 + 6;
const int maxc = 63;
int ch[maxn][maxc];
char s[maxn];
int tot = 1;
int siz[maxn];
// int cnt[maxn];
inline int getid(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    else if (c >= 'a' && c <= 'z')
        return c - 'a' + 26;
    else
        return c - '0' + 52;
}
void insert(char *str)
{
    int p = 1;
    for (int i = 0, l = strlen(str); i < l; i++)
    {
        if (!ch[p][getid(str[i])])
            ch[p][getid(str[i])] = ++tot;
        p = ch[p][getid(str[i])];
        siz[p]++;
    }
    // cnt[p]++;
}
int find(char *str)
{
    int p = 1;
    for (int i = 0, l = strlen(str); i < l; i++)
    {
        if (!ch[p][getid(str[i])])
            return 0;
        p = ch[p][getid(str[i])];
    }
    return siz[p];
}
int main()
{
    ios::sync_with_stdio(false);
    int t = 0;
    cin >> t;
    while (t--)
    {
        for (int i = 0; i < tot; i++)
        {
            siz[i] = 0;
            for (int j = 0; j < 63; j++)
            {
                ch[i][j] = 0;
            }
        }
        // memset(ch,0,sizeof(ch));
        tot = 1;
        // memset(cnt,0,sizeof(cnt));
        // memset(siz,0,sizeof(siz));
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++)
        {
            cin >> s;
            insert(s);
        }
        for (int i = 0; i < q; i++)
        {
            cin >> s;
            cout << find(s) << "\n";
        }
    }
    return 0;
}
