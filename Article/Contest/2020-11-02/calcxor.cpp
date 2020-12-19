#include <cstdio>
int n = 0;
int s[100003];
int main() {
	freopen("calcxor.in", "r", stdin);
	freopen("calcxor.out", "w", stdout);
	scanf("%d", &n);
	int ans = 0, p = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &p);
		s[i] = s[i - 1] ^ i;
		ans ^= p;
		if ((n / i) & 1) ans ^= s[i - 1];
		ans ^= s[n % i];
	}
	printf("%d", ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
