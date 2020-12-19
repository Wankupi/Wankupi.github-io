#include <cstdio>
#include <algorithm>
using namespace std;
int const maxn = 100003;
inline int read() {
	int x = 0, c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while ('0' <= c && c <= '9') x = 10 * x + c - '0', c = getchar();
	return x;
}
typedef long long ll;
int n = 0, m = 0;
int a[maxn], A[maxn], cA = 0;
void solve1() {
	static int t[503];
	int l = 0, r = 0;
	for (int i = 1; i <= m; ++i) {
		l = read(); r = read();
		for (int j = l; j <= r; ++j) t[j - l] = a[j];
		sort(t, t + r - l + 1);
		ll U = 1;
		for (int j = 0; j < r - l + 1; ++j) if (t[j] <= U) U += t[j]; else break;
		printf("%lld\n", U);
	}
}
struct Node {
	ll sum;
	int lc, rc;
};
Node tr[maxn * 40];
int cntNode = 0;
void add(int &p, int L, int R, int x) {
	tr[++cntNode] = tr[p]; p = cntNode;
	if (L == R) {
		tr[p].sum += A[x];
		return;
	}
	int mid = (L + R) >> 1;
	if (x <= mid) add(tr[p].lc, L, mid, x);
	else add(tr[p].rc, mid + 1, R, x);
	tr[p].sum = tr[tr[p].lc].sum + tr[tr[p].rc].sum;
}
ll query(int p, int L, int R, int x) { // 查询所有值小于等于x的数的和
	if (p == 0 || x < L) return 0;
	if (R <= x) return tr[p].sum;
	int mid = (L + R) >> 1;
	if (x <= mid) return query(tr[p].lc, L, mid, x);
	else return tr[tr[p].lc].sum + query(tr[p].rc, mid + 1, R, x);
}
int rt[maxn];

void solve2() {
	for (int i = 1; i <= n; ++i) A[i] = a[i];
	sort(A + 1, A + n + 1);
	cA = unique(A + 1, A + n + 1) - A - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(A + 1, A + cA + 1, a[i]) - A;
	for (int i = 1; i <= n; ++i) {
		rt[i] = rt[i - 1];
		add(rt[i], 1, cA, a[i]);
	}
	int qL = 0, qR = 0;
	for (int i = 1; i <= m; ++i) {
		qL = read(); qR = read();
		ll last = 1;
		while (true) {
			int pos = (last <= A[cA]) ? int(upper_bound(A + 1, A + cA + 1, int(last)) - A - 1) : cA;
			ll x = query(rt[qR], 1, cA, pos) - query(rt[qL - 1], 1, cA, pos) + 1;
			if (x <= last) break;
			else last = x;
		}
		printf("%lld\n", last);
	}
}
int main() {
	n = read(); m = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	solve2();
	// if (n <= 500 && m <= 500) solve1();
	// else solve2();
	return 0;
}