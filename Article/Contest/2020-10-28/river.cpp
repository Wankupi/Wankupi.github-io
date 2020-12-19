#include <algorithm>
#include <cstdio>
typedef long long ll;

int n = 0, L = 0, a[100003];
ll s[100003];

int main() {
	scanf("%d %d", &n, &L);
	for (int i = 1; i < n; ++i) {
		scanf("%d", a + i);
		s[i] = s[i - 1] + a[i];
	}
	ll ans = 0x7fffffffffffffff;
	for (int i = L; i < n; ++i)
		ans = std::min(ans, s[i] - s[i - L]);
	printf("%lld", ans);
	return 0;
}