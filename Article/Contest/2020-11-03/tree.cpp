#include <cstdio>
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return x;
}
int const maxn = 100003;
int n = 0, m = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }

int opts[maxn], X[maxn];

int vis[maxn], limit = 0;
int q[maxn], ql = 1, qr = 0;

void solve(int l, int r) {
	if (l > r) return;
	for (int i = l; i <= r; ++i) {
		int opt = opts[i], x = X[i];
		if (opt == 1) {
			if (vis[x] <= limit) {
				q[++qr] = x;
				vis[x] = i;
			}
		}
		else if (opt == 2) { ql = 1; qr = 0; limit = i; }
		else puts(vis[x] > limit ? "wrxcsd" : "orzFsYo");
		int R = qr;
		while (ql <= R) {
			int x = q[ql++];
			for (int i = head[x]; i; i = nxt[i]) if (vis[to[i]] <= limit) {
				vis[to[i]] = vis[x];
				q[++qr] = to[i];
			}
		}
	}
}
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	n = read(); m = read();
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) { x = read(); y = read(); insert(x, y); insert(y, x); }
	bool isQuery = false;
	int left = 1;
	for (int i = 1; i <= m; ++i) {
		opts[i] = read(); X[i] = read();
		if (opts[i] == 2) {
			if (isQuery) solve(left, i - 1);
			isQuery = false;
			left = i;
			ql = 1; qr = 0;
		}
		else if (opts[i] == 3) isQuery = true;
	}
	if (left <= m && isQuery) solve(left, m);
	fclose(stdin); fclose(stdout);
	return 0;
}
