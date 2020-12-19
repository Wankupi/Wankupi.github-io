#include <cstdio>
#include <random>
#include <map>
using namespace std;
int n = 0, m = 0, q = 0;
unsigned int s[2003][2003];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y, unsigned int v) {
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= m; j += lowbit(j))
			s[i][j] ^= v;
}
inline unsigned int query(int x, int y) {
	unsigned int sum = 0;
	for (int i = x; i >= 1; i -= lowbit(i))
		for (int j = y; j >= 1; j -= lowbit(j))
			sum ^= s[i][j];
	return sum;
}
inline void addSq(int x1, int y1, int x2, int y2, unsigned v) {
	add(x1, y1, v);
	add(x2 + 1, y2 + 1, v);
	add(x1, y2 + 1, v);
	add(x2 + 1, y1, v);
}
struct Sq {
	int x1, y1, x2, y2;
};
inline bool operator<(Sq const &A, Sq const &B) {
	if (A.x1 == B.x1) {
		if (A.y1 == B.y1) {
			if (A.x2 == B.x2)
				return A.y2 < B.y2;
			return A.x2 < B.x2;
		}
		return A.y1 < B.y1;
	}
	return A.x1 < B.x1;
}
map<Sq, unsigned int> rv;
int main() {
	scanf("%d %d %d", &n, &m, &q);
	int opt = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned int> u;
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d %d %d %d", &opt, &x1, &y1, &x2, &y2);
		if (opt == 1) {
			rv[Sq{x1,y1,x2,y2}] = u(e);
			addSq(x1, y1, x2, y2, rv[Sq{x1, y1, x2, y2}]);
		}
		else if (opt == 2)
			addSq(x1, y1, x2, y2, rv[Sq{x1, y1, x2, y2}]);
		else
			printf(query(x1, y1) == query(x2, y2) ? "Yes\n" : "No\n");
	}
	return 0;
}