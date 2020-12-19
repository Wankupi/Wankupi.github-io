#include <cstdio>
#include <cmath>
int const maxn = 100003;
int Testcase = 0, n = 0, pointO = 0, pointTar = 0, A = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int power[maxn], point[maxn];
int d[maxn];

double V = 0.0;
inline double delta(double poi1, double pow2, double poi2) {
	double a = V > pow2 ? +1 : -1, b = poi1 > poi2 ? +1 : -1;
	return 2 * a * (sqrt(fabs(V - pow2) + 1) - 1) - A * b * (sqrt(fabs(poi1 - poi2) + 1) - 1);
}

double f[maxn][2]; int fr[maxn];
inline void update(int x, double v, int y) {
	if (v > f[x][0]) { f[x][1] = f[x][0]; f[x][0] = v; fr[x] = y; }
	else if (v > f[x][1]) f[x][1] = v;
}

void dfs1(int x, int fa) {
	if (d[x] <= 1) update(x, delta(pointO, power[x], point[x]) + pointO, 0);
	for (int i = head[x]; i; i = nxt[i]) if (to[i] != fa) {
		dfs1(to[i], x);
		update(x, delta(f[to[i]][0], power[x], point[x]) + f[to[i]][0], to[i]);
	}
}
void dfs2(int x, int fa) {
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != fa) {
			if (fr[x] == to[i]) update(to[i], delta(f[x][1], power[to[i]], point[to[i]]) + f[x][1], x);
			else update(to[i], delta(f[x][0], power[to[i]], point[to[i]]) + f[x][0], x);
			dfs2(to[i], x);
		}
}
bool check() {
	for (int i = 1; i <= n; ++i) f[i][0] = f[i][1] = fr[i] = 0;
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; ++i) if (d[i] <= 1 && f[i][0] >= pointTar) return true;
	return false;
}

int main() {
	scanf("%d", &Testcase);
	scanf("%d %d %d %d", &n, &pointO, &pointTar, &A);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y); insert(y, x); ++d[x]; ++d[y];
	}
	for (int i = 1; i <= n; ++i) scanf("%d %d", power + i, point + i);
	double L = -100000.0, R = 100000000.0;
	for (int i = 1; i <= 60; ++i) {
		V = (L + R) * 0.5;
		if (check()) R = V;
		else L = V;
	}
	printf("%.6lf", L);
	return 0;
}