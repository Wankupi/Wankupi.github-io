#include <algorithm>
#include <cstdio>
using namespace std;
int n = 0, m = 0;
struct S_10 {
	int a[10];
	int &operator[](int x) { return a[x]; }
	S_10 inv();
};
S_10 S_10::inv() {
	S_10 r;
	for (int i = 0; i < 10; ++i)
		r[a[i]] = i;
	return r;
}
S_10 operator*(S_10 A, S_10 &B) {
	for (int i = 0; i < 10; ++i)
		A[i] = B[A[i]];
	return A;
}
S_10 s[100003];
int p[10];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < 10; ++i)
		p[i] = s[0][i] = i;
	int x = 0, y = 0;
	for (int i = 1; i <= n; ++i) {
		s[i] = s[i - 1];
		scanf("%d %d", &x, &y);
		std::swap(p[x], p[y]);
		std::swap(s[i][p[x]], s[i][p[y]]);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &x, &y);
		S_10 r = (s[x - 1].inv() * s[y]).inv();
		for (int j = 0; j < 9; ++j)
			printf("%d ", r[j]);
		printf("%d\n", r[9]);
	}
	return 0;
}