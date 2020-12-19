#include <cstdio>
typedef long long ll;
ll p1 = 998244353, p2 = p1 - 1;
inline ll dec(ll a, ll b) { return a >= b ? a - b : a - b + p1; }
ll pow(ll x, ll b, ll mod) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * x % mod;
		x = x * x % mod;
		b >>= 1;
	}
	return r;
}
ll fact[300003], inv[300003];
int prime[100000], cPrime = 0;
bool h[300003]; int mu[300003];
void euler() {
	h[1] = true; mu[1] = 1;
	for (int i = 2; i <= 300000; ++i) {
		if (!h[i]) {
			prime[cPrime++] = i; mu[i] = -1;
		}
		for (int j = 0; j < cPrime && prime[j] * i <= 300000; ++j) {
			h[prime[j] * i] = true;
			if (i % prime[j]) mu[prime[j] * i] = -mu[i];
			else break;
		}
	}
}
ll f[300003], sf[300003];
void init() {
	fact[0] = 1;
	for (int i = 1; i <= 300000; ++i) fact[i] = fact[i - 1] * i % p1, f[i] = 1;
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= 300000; ++i) inv[i] = (p1 - p1 / i) * inv[p1 % i] % p1;
	euler();
	for (int i = 1; i <= 300000; ++i)
		for (int j = i; j <= 300000; j += i) {
			if (mu[j / i] == 1) f[j] = f[j] * i % p1;
			else if (mu[j / i] == -1) f[j] = f[j] * inv[i] % p1;
		}
	sf[0] = 1;
	for (int i = 1; i <= 300000; ++i) sf[i] = sf[i - 1] * f[i] % p1;
}
int n = 0; ll k = 0;
int main() {
	init();
	int T = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %lld", &n, &k);
		ll Down = 1;
		for (int l = 1, r = 0; l <= n; l = r + 1) {
			ll d = n / l; r = n / d;
			ll v = sf[r] * pow(sf[l - 1], p1 - 2, p1) % p1, t = pow(d, k, p2);
			Down = Down * pow(v, t, p1) % p1;
		}
		ll Up = pow(fact[n], k % p2 * pow(n, k - 1, p2) % p2, p1);
		ll Ans = Up * pow(Down, p1 - 2, p1) % p1;
		printf("%lld\n", Ans);
	}
	return 0;
}