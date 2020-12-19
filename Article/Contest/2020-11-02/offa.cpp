#include <cstdio>

inline char gc() {
	static char now[1 << 20], *S, *T;
	if (T == S) {
		T = (S = now) + fread(now, 1, 1 << 20, stdin);
		if (T == S) return EOF;
	}
	return *S++;
} //getchar
inline int read() {
	int res = 0, sign = 1;
	char c;
	while ((c = gc()) < '0' || c > '9') if (c == '-') sign = -1;
	res = (c ^ 48);
	while ((c = gc()) >= '0' && c <= '9') res = (res << 3) + (res << 1) + (c ^ 48);
	return res * sign;
} //read a signed interger

typedef long long ll;
ll const inf = 0x3f3f3f3f3f3f3f3f;
int const maxn = 5000003;
int n = 0, m = 0;
int a[maxn], p[maxn], b[maxn], pos[maxn];
ll tr[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(int p, int v) { while (p > 0) { tr[p] += v; p -= lowbit(p); } }
inline ll query(int p) { ll sum = 0; while (p <= n + 1) { sum += tr[p]; p += lowbit(p); } return sum; }

ll F[maxn]; int cnt[maxn];
void solve() {
	cnt[0] = 1;
	for (int i = 1; i <= m; ++i) F[i] = inf;
	for (int i = 1; i <= n; ++i) {
		int k = pos[a[i]];
		ll f = 0;
		if (k && cnt[k - 1] > 0) {
			ll sum = query(b[k - 1] + 1);
			f = sum + F[k - 1];
		}
		add(p[i] >= 0 ? a[i] : (n + 1), p[i]);
		if (k && cnt[k - 1] > 0) {
			ll df = f - query(b[k] + 1);
			if (F[k] > df) F[k] = df;
			++cnt[k];
		}
	}
	if (cnt[m] == 0) { puts("Impossible"); return; }
	ll f = F[m] + query(b[m] + 1);
	printf("%lld\n", f);
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) p[i] = read();
	m = read();
	for (int i = 1; i <= m; ++i) { b[i] = read(); pos[b[i]] = i; }
	solve();
	return 0;
}
