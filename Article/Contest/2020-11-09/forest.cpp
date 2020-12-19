#include <cstdio>
#include <queue>
#include <algorithm>
int const maxn = 2003;
int const dx[] = {-1, -1, 0, +1, +1, +1, 0, -1},
		  dy[] = {0, -1, -1, -1, 0, +1, +1, +1};
int n = 0, m = 0;
char a[maxn][maxn];
int dis[maxn][maxn];
struct Point { int x, y; };
Point S, firstTree;
void bfs() {
	for (int i = 0; i <= n + 1; ++i) for (int j = 0; j <= m + 1; ++j) dis[i][j] = 0x3f3f3f3f;
	dis[S.x][S.y] = 0;
	std::queue<Point> q;
	q.push(S);
	while (q.size()) {
		Point p = q.front(); q.pop();
		for (int d = 0; d < 8; ++d) {
			Point t{p.x + dx[d], p.y + dy[d]};
			if (t.x < 1 || t.x > n || t.y < 1 || t.y > m) continue;
			if (a[t.x][t.y] != '.') continue;
			if (dis[t.x][t.y] > dis[p.x][p.y] + 1) {
				dis[t.x][t.y] = dis[p.x][p.y] + 1;
				q.push(t);
			}
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1;i  <= n; ++i) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= m; ++j)
			if (a[i][j] == '*') S = Point{i,j};
			else if (a[i][j] == 'X' && firstTree.x == 0)
				firstTree = Point{i, j};
	}
	int X = firstTree.x;
	for (int j = 1; j < firstTree.y; ++j)
		a[X][j] = '?';
	bfs();
	int ans = 0x3f3f3f3f;
	for (int j = 1; j < firstTree.y; ++j) {
		int d1 = std::min(std::min(dis[X - 1][j - 1], dis[X - 1][j]), dis[X - 1][j + 1]);
		int d2 = std::min(std::min(dis[X + 1][j - 1], dis[X + 1][j]), dis[X + 1][j + 1]);
		ans = std::min(ans, d1 + d2 + 2);
	}
	printf("%d", ans);
	return 0;
}