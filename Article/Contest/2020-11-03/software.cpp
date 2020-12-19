#include <cstdio>
#include <algorithm>
using namespace std;
int n = 0, m = 0;
int d1[103], d2[103];
int f[2][103];
bool check(int t) {
	for (int i = 1; i <= m; ++i) f[0][i] = -100000;
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) f[i & 1][j] = -100000;
		for (int p = 0; p <= t / d1[i]; ++p) {
			int q = (t - d1[i] * p) / d2[i];
			for (int j = m; j >= p; --j)
				f[i & 1][j] = std::max(f[i & 1][j], f[(i & 1) ^ 1][j - p] + q);
			if (f[i & 1][m] >= m) return true;
		}
	}
	return false;
}
int main() {
	freopen("software.in", "r", stdin);
	freopen("software.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d %d", d1 + i, d2 + i);
	int L = 1, R = 10000;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (check(mid)) R = mid - 1;
		else L = mid + 1;
	}
	printf("%d", R + 1);
	fclose(stdin); fclose(stdout);
	return 0;
}
