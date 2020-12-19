#include <cstdio>
typedef long long ll;
inline ll abs(ll x) { return x < 0 ? -x : x; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
int main() {
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		long long a = 0, b = 0, c = 0, d = 0;
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		ll k = gcd(gcd(abs(a), abs(b)), abs(c));
		if (k == 0)
			puts(d == 0 ? "YES" : "NO");
		else
			puts(abs(d) % k == 0 ? "YES" : "NO");
	}
	return 0;
}