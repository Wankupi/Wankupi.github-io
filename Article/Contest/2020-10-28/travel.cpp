#include <cstdio>
typedef long long ll;
ll const mod = 998244353;
int const maxn = 200003;
inline ll pls(ll a, ll b) { return a + b < mod ? a + b : a + b - mod; }
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + mod; }
int n = 0;
int a[maxn], d[maxn]; // meaning of d[] is changed: the max points can go by.
int F[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int fa[maxn];
int st[maxn], top = 0;
void dfs1(int x, int f) {
	fa[x] = f;
	st[++top] = x;
	int up = d[x] <= top ? st[top - d[x] + 1] : st[1];
	F[x] = pls(F[x], a[x]); F[fa[up]] = dec(F[fa[up]], a[x]);
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) {
			dfs1(to[i], x);
			F[x] = pls(F[x], F[to[i]]);
		}
	--top;
}

ll E[maxn], E2[maxn];
void dfs3(int x) {
	E[x] = F[x]; E2[x] = ll(F[x]) * F[x] % mod;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			int y = to[i];
			dfs3(y);
			E2[x] = pls(E2[x], pls(E2[y] * val[i] % mod, 2 * E[x] * E[y] % mod * val[i] % mod));
			E[x] = pls(E[x], E[y] * val[i] % mod);
		}
}
void dfs4(int x) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa[x]) {
			int y = to[i];
			ll dE = dec(E[x], E[y] * val[i] % mod);
			ll dE2 = dec(E2[x], pls(E2[y] * val[i] % mod, 2 * dE * E[y] % mod * val[i] % mod));
			E2[y] = pls(E2[y], pls(dE2 * val[i] % mod, 2 * E[y] * dE % mod * val[i] % mod));
			E[y] = pls(E[y], dE * val[i] % mod);
			dfs4(to[i]);
		}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) { scanf("%d %d", a + i, d + i); ++d[i]; }
	int x = 0, y = 0, z = 0;
	for (int i = 1; i < n; ++i) { scanf("%d %d %d", &x, &y, &z); insert(x, y, z); }
	dfs1(1, 0);
	dfs3(1); dfs4(1);
	int Q = 0;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; ++i) { scanf("%d", &x); printf("%lld\n", E2[x]); }
	return 0;
}