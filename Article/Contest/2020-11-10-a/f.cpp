#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
int n = 0;
int a[100003];
set<ll> fib;
void init(ll limit) {
	fib.insert(1);
	ll a = 1, b = 1;
	while (a <= limit) {
		b += a;
		swap(a, b);
		fib.insert(a);
	}
}

int main() {
	scanf("%d", &n);
	int Mx = 0;
	for (int i = 1; i <= n; ++i) { scanf("%d", a + i); if (a[i] > Mx) Mx = a[i]; }
	init(Mx * 2);
	set<int> now;
	int cnt = 1;
	now.insert(a[1]);
	for (int i = 2; i <= n; ++i) {
		bool addable = true;
		for (set<ll>::iterator p = fib.begin(); p != fib.end(); ++p)
			if (now.find(*p - a[i]) != now.end()) {
				addable = false;
				break;
			}
		if (!addable) {
			now.clear();
			++cnt;
		}
		now.insert(a[i]);
	}
	printf("%d\n", cnt);
	return 0;
}