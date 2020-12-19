#include <cstdio>
int n = 0, m = 0;
int a[100003];
int tr[100003];
inline int lowbit(int x) { return x & -x; }
void modi(int p, int v) {
	while (p > 0) {
		tr[p] |= v;
		p -= lowbit(p);
	}
}
int query(int p) {
	int r = 0;
	while (p <= n) { r |= tr[p]; p += lowbit(p); }
	return r;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	long long sum = 0;
	for (int i = 1, j = 1; i <= n; ++i) {
		modi(i, a[i]);
		while (j < i && query(j) >= m) ++j;
		sum += i - j; 
	}
	printf("%lld", sum);
	return 0;
}