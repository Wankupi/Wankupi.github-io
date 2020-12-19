#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int const maxn = 500003;
struct LSR {
	int a, b;
};
inline bool operator<(LSR const &lhs, LSR const &rhs) { return lhs.a == rhs.a ? lhs.b > rhs.b : lhs.a > rhs.a; }
int n = 0;
LSR o[maxn];
ll sa[maxn], sb[maxn];
int main() {
	freopen("games.in", "r", stdin);
	freopen("games.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d %d", &o[i].a, &o[i].b);
	std::sort(o + 1, o + n + 1);
	for (int i = 1; i <= n; ++i) {
		sa[i] = sa[i - 1] + o[i].a;
		sb[i] = sb[i - 1] + o[i].b;
	}
	int q = 0; ll k = 0, m = 0;
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		scanf("%lld %lld", &k, &m);
		printf("%lld\n", sa[m] * k + sb[m]);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
