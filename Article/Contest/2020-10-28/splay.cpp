#include <cstdio>
#include <algorithm>
typedef long long ll;
ll mod = 1000000007;
int const maxn = 200003;
int n = 0, Q = 0;
int w[maxn], son[maxn][2], fa[maxn];
ll s[maxn];
int dfn[maxn], idfn[maxn], cdfn = 0;
int l[maxn], r[maxn];
void dfs(int x) {
	if (son[x][0]) { fa[son[x][0]] = x; dfs(son[x][0]); }
	idfn[dfn[x] = ++cdfn] = x;
	if (son[x][1]) { fa[son[x][1]] = x; dfs(son[x][1]); }
	l[x] = (son[x][0] ? l[son[x][0]] : dfn[x]);
	r[x] = (son[x][1] ? r[son[x][1]] : dfn[x]);
	s[x] = (w[x] + (son[x][0] ? s[son[x][0]] : 0) + (son[x][1] ? s[son[x][1]] : 0)) % mod;
}
ll muti[maxn << 4];
void Create(int p, int L, int R) {
	if (L == R) { muti[p] = s[idfn[L]]; return; }
	int mid = (L + R) >> 1;
	Create(p << 1, L, mid);
	Create(p << 1 | 1, mid + 1, R);
	muti[p] = muti[p << 1] * muti[p << 1 | 1] % mod;
}
void Set(int p, int L, int R, int x) {
	if (L == R) { muti[p] = s[idfn[L]]; return; }
	int mid = (L + R) >> 1;
	if (x <= mid) Set(p << 1, L, mid, x);
	else Set(p << 1 | 1, mid + 1, R, x);
	muti[p] = muti[p << 1] * muti[p << 1 | 1] % mod;
}
ll query(int p, int L, int R, int l, int r) {
	if (l <= L && R <= r) return muti[p];
	int mid = (L + R) >> 1;
	if (r <= mid) return query(p << 1, L, mid, l, r);
	else if (l > mid) return query(p << 1 | 1, mid + 1, R, l, r);
	else return query(p << 1, L, mid, l, r) * query(p << 1 | 1, mid + 1, R, l, r) % mod;
}
inline int iden(int x) { return son[fa[x]][1]== x; }
inline void update(int x) {
	l[x] = (son[x][0] ? l[son[x][0]] : dfn[x]);
	r[x] = (son[x][1] ? r[son[x][1]] : dfn[x]);
	s[x] = (w[x] + (son[x][0] ? s[son[x][0]] : 0) + (son[x][1] ? s[son[x][1]] : 0)) % mod;
	Set(1, 1, n, dfn[x]);
}
inline void connect(int ch, int f, int rela) {
	if (f) son[f][rela] = ch;
	if (ch) fa[ch] = f;
}
void rotate(int x) {
	int f = fa[x], z = fa[f], m = iden(x);
	connect(x, z, son[z][1] == f);
	connect(son[x][m ^ 1], f, m);
	connect(f, x, m ^ 1);
	update(f); update(x);
}
int main() {
	scanf("%d %d", &n, &Q);
	for (int i = 1; i <= n; ++i)
		scanf("%d %d %d", w + i, &son[i][0], &son[i][1]);
	dfs(1);
	Create(1, 1, n);
	int opt = 0, x = 0;
	for (int i = 1; i <= Q; ++i) {
		scanf("%d %d", &opt, &x);
		if (opt == 0 && son[x][0]) rotate(son[x][0]);
		else if (opt == 1 && son[x][1]) rotate(son[x][1]);
		else if (opt == 2) printf("%lld\n", query(1, 1, n, l[x], r[x]));
	}
	return 0;
}