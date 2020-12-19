#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll base = 47, p = 327, mod = 998244353;
int n = 0, m = 0;
char str[200003];
long long sum[200003][26], mi[200003];
int a[26], b[26];
int main() {
	scanf("%d %d", &n, &m);
	scanf("%s", str + 1);
	mi[0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 26; ++j)
			sum[i][j] = sum[i - 1][j] * p % mod;
		sum[i][str[i] - 'a'] += base;
		mi[i] = mi[i - 1] * p % mod;
	}
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		for (int j = 0; j < 26; ++j) {
			a[j] = (sum[x + z - 1][j] - sum[x - 1][j] * mi[z] % mod + mod) % mod;
			b[j] = (sum[y + z - 1][j] - sum[y - 1][j] * mi[z] % mod + mod) % mod;
		}
		sort(a, a + 26);
		sort(b, b + 26);
		bool sign = true;
		for (int j = 0; j < 26; ++j) sign = sign && a[j] == b[j];
		puts(sign ? "YES" : "NO");
	}
	return 0;
}