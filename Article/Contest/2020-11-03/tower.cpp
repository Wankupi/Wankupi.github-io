#include <cstdio>
#include <set>
using namespace std;
using ll = long long;
struct Character {
	ll hit, reward; // hit 总伤害 reward 蓝宝石收益
	int id;
};
inline bool operator<(Character const &lhs, Character const &rhs) { return lhs.reward * rhs.hit > rhs.reward * lhs.hit; }
using Ptr = multiset<Character>::iterator;
int const maxn = 100003;

int n = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
inline void insert(int u, int e) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; }
int fa[maxn];
void dfs(int x, int f) {
	fa[x] = f;
	for (int i = head[x]; i; i = nxt[i])
		if (to[i] != f) dfs(to[i], x);
}

struct GW {
	int blood, force, defence, reward;
};
GW a[maxn];
ll B = 0, F = 0, D = 0;
multiset<Character> s;
Ptr p[maxn];
int bc[maxn]; // 并查集
inline int find(int x) { return bc[x] == x ? x : bc[x] = find(bc[x]); }
int ed[maxn],last[maxn];
int main() {
	scanf("%d", &n);
	int x = 0, y = 0;
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	dfs(1, 0);
	scanf("%lld %lld %lld", &B, &F, &D);
	bc[1] = ed[1] = 1;
	for (int i = 2; i <= n; ++i) {
		scanf("%d %d %d %d", &a[i].blood, &a[i].force, &a[i].defence, &a[i].reward);
		Character ch{(a[i].blood / (F - a[i].defence) - (a[i].blood % (F - a[i].defence) == 0)), a[i].reward, i};
		p[i] = s.insert(ch);
		bc[i] = ed[i] = i;
	}
	for (int i = 1; i < n; ++i) {
		Character ch = *s.begin();
		s.erase(s.begin());
		int Fa = find(fa[ch.id]);
		last[ed[Fa]] = ch.id;
		ed[Fa] = ed[ch.id];
		bc[ch.id] = Fa;
		if (Fa != 1) {
			Character fx = *p[Fa];
			s.erase(p[Fa]);
			fx.hit += ch.hit; fx.reward += ch.reward;
			p[Fa] = s.insert(fx);
		}
	}
	for (int i = 1, x = 1; i < n; ++i) {
		x = last[x];
		B -= ((a[x].blood + (F - a[x].defence - 1)) / (F - a[x].defence) - 1ll) * (a[x].force - D);
		D += a[x].reward;
	}
	printf("%lld\n", B);
	return 0;
}