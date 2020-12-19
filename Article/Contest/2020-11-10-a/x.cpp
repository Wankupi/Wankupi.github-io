#include <cstdio>
typedef long long ll;
int const maxn = 100007;
int n = 0, m = 0;
int a[maxn];
ll calc(int L, int R, int V); // 求多少个区间长度在[L,R]中，中位数严格小于V
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
		scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
		ll A = calc(l2, r2, r1 + 1), B = calc(l2, r2, l1);
		ll ans = A - B;
		printf("%lld\n", ans);
	}
	return 0;
}
int s[maxn];
int tr[maxn << 1]; int const delta = 100001;
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) {
	p += delta;
	while (p <= n + delta) { tr[p] += v; p += lowbit(p); }
}
inline int query(int p) {
	p += delta; int r = 0;
	while (p > 0) { r += tr[p]; p -= lowbit(p); }
	return r;
}
ll calc(int L, int R, int V) {
	s[0] = 0;
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + (a[i] >= V ? +1 : -1);
	for (int i = 0; i <= n + delta; ++i) tr[i] = 0;
	ll ans = 0;
	for (int i = L; i <= n; ++i) {
		add(s[i - L], +1);
		if (i - R - 1 >= 0) add(s[i - R - 1], -1);
		ans += query(n) - query(s[i] - 1);
	}
	return ans;
}