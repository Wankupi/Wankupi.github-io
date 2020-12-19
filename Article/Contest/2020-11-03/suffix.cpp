#include <cstdio>
#include <assert.h>
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9')
		x = 10 * x + c - '0', c = getchar();
	return x;
}
int const maxn = 1000003;
int n = 0;
int fa[maxn], v[maxn];
int head[maxn], nxt[maxn], to[maxn], cnt = 0;
inline void insert(int u, int e) {
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = e;
}
int st[maxn], top = 0;
int last[maxn], old[maxn];
int ans[maxn];
int erfen(int x) {
	int L = 1, R = top;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (st[mid] >= x) L = mid + 1;
		else R = mid - 1;
	}
	return R + 1;
}
void dfs(int x) {
	last[x] = top;
	top = erfen(v[x]);
	old[x] = st[top];
	st[top] = v[x];
	ans[x] = top;
	for (int i = head[x]; i; i = nxt[i])
		dfs(to[i]);
	st[top] = old[x];
	top = last[x];
}
int main() {
	freopen("suffix.in", "r", stdin);
	freopen("suffix.out", "w", stdout);
	n = read();
	for (int i = 2; i <= n; ++i) {
		fa[i] = read();
		insert(fa[i], i);
	}
	for (int i = 1; i <= n; ++i)
		v[i] = read();
	dfs(1);
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}