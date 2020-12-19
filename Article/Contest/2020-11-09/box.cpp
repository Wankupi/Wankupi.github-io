#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n = 0, a[81], b[81], sa = 0;
int f[81][1603];
int ans[81];
int main() {
	freopen("box.in", "r", stdin);
	freopen("box.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) { scanf("%d", a + i); sa += a[i]; }
	for (int i = 1; i <= n; ++i) scanf("%d", b + i);
	memset(f, -0x3f, sizeof f);
	f[0][0] = 0;
	int sumb = 0;
	for (int i = 1; i <= n; ++i) {
		sumb += b[i];
		for (int j = i; j >= 1; --j) {
			for (int p = sumb; p >= b[i]; --p)
				f[j][p] = std::max(f[j][p], f[j - 1][p - b[i]] + a[i]);
		}
	}
	for (int j = 1; j <= n; ++j) {
		ans[j] = 100000000;
		for (int p = sa; p <= sumb; ++p) ans[j] = min(ans[j], sa - f[j][p]);
		if (ans[j] == 100000000) ans[j] = -1;
	}
	int q = 0, k = 0; scanf("%d", &q);
	for (int i = 1; i <= q; ++i) { scanf("%d", &k); printf("%d\n", ans[k]); }
	fclose(stdin); fclose(stdout);
	return 0;
}
