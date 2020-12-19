#include <algorithm>
#include <cstdio>
#include <cmath>
typedef long long ll;
int const maxn = 100003, maxP = maxn * 20;
ll const inf = 0x3f3f3f3f3f3f3f3f;
inline int read() {
	int x = 0, c = getchar(), f = +1;
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return f * x;
}
int n = 0, m = 0;
int val[maxn], buff[maxn];
inline int id(int x, int y) { return (x - 1) * m + y; }
ll f[maxn];

struct Line {
	ll k, b;
	ll operator()(int x) { return k * x + b; }
};
Line tr[maxP];
int lc[maxP], rc[maxP], cntP = 0;

void add(int &p, int L, int R, Line a) {
	if (p == 0) { p = ++cntP; tr[p] = a; return; }
	ll nL = a(L), nR = a(R), oL = tr[p](L), oR = tr[p](R);
	if (nL >= oL && nR >= oR) { tr[p] = a; return; }
	else if (nL <= oL && nR <= oR) return;
	int mid = int(floor((L + R) / 2.0)); // 下取整 not= 向中
	ll nM = a(mid), oM = tr[p](mid);
	if (nM >= oM) { std::swap(tr[p], a); std::swap(nL, oL); std::swap(nR, oR); std::swap(nM, oM); }
	if (nL > oL) add(lc[p], L, mid, a);
	else add(rc[p], mid + 1, R, a);
}

ll query(int p, int L, int R, int x) {
	if (p == 0) return -inf;
	ll v = tr[p](x);
	if (L == R) return v;
	int mid = int(floor((L + R) / 2.0));
	if (x <= mid) return std::max(v, query(lc[p], L, mid, x));
	else return std::max(v, query(rc[p], mid + 1, R, x));
}

int root[maxn];
inline int lowbit(int x) { return x & -x; }
void Modify(int p, Line a) {
	while (p > 0) {
		add(root[p], -10000, 10000, a);
		p -= lowbit(p);
	}
}
ll Query(int p, int x) {
	ll ans = -inf;
	while (p <= m) {
		ans = std::max(ans, query(root[p], -10000, 10000, x));
		p += lowbit(p);
	}
	return ans;
}
void solve() {
	for (int i = n; i >= 1; --i) {
		for (int j = m; j >= 1; --j) {
			ll v = Query(j, buff[id(i, j)]);
			f[id(i, j)] = v + val[id(i, j)] - (ll)buff[id(i, j)] * (i + j);
			if (i == n && j == m) f[id(i, j)] = 0;
			Modify(j, Line{i + j, f[id(i, j)]});
		}
	}
}
int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n * m; ++i)
		buff[i] = read();
	for (int i = 1; i <= n * m; ++i)
		val[i] = read();
	solve();
	printf("%lld\n", f[id(1, 1)]);
	return 0;
}