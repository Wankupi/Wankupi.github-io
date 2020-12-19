#include <cstdio>
int const N = 1000003, bit = 29;
int n = 0, k = 0;
int tr[N * 30][2], siz[N * 30], cnt = 1;

inline void insert(int x) {
	++siz[1];
	int p = 1;
	for (int j = bit; ~j; --j) {
		int c = (x >> j) & 1;
		if (tr[p][c] == 0) siz[tr[p][c] = ++cnt] = 0;
		p = tr[p][c];
		++siz[p];
	}
}
inline int query(int x) {
	int p = 1, sum = 0;
	for (int j = bit; ~j && p; --j) {
		int cx = (x >> j) & 1, ck = (k >> j) & 1;
		if (ck == 0) sum += siz[tr[p][cx ^ 1]];
		p = tr[p][cx ^ ck];
	}
	return sum + (p != 0 ? siz[p] : 0);
}
int main() {
	scanf("%d %d", &n, &k);
	int x = 0, s = 0;
	insert(0);
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x);
		s ^= x;
		ans += query(s);
		insert(s);
	}
	printf("%lld", ans);
	return 0;
}