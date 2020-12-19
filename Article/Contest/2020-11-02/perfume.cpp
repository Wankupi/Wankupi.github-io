#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;
int n = 0, k = 0;
ll p[50]; int cnt = 0;
ll mabs(ll x) { return x < 0 ? -x : x; }
int main() {
	freopen("perfume.in", "r", stdin);
	freopen("perfume.out", "w", stdout);
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &k);
		if (k == 1) { p[0] = 1; cnt = 1; }
		else if (k == -1) { p[0] = 1; p[1] = -1; cnt = 2; }
		else {
			cnt = 0;
			for (ll v = 1; mabs(v) <= 1000000000000000; v *= k) p[cnt++] = v;
		}
		map<ll, int> m;
		m[0] = 1;
		ll sum = 0, x = 0, ans = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &x);
			sum += x;
			for (int j = 0; j < cnt; ++j)
				if (m.find(sum - p[j]) != m.end())
					ans += m[sum - p[j]];
			++m[sum];
		}
		printf("%lld\n", ans);
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
