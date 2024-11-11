```c++
const int INF = INT_MAX;  // 无穷大，用于初始化最短路径
const int MAXN = 1000;

void dijkstra(int start, int n, const int graph[MAXN][MAXN]) {
	int dist[MAXN];       // dist[i] 表示从 start 到节点 i 的最短距离
	bool visited[MAXN];   // visited[i] 标记节点 i 是否已访问

	// 初始化
	fill(dist, dist + n, INF); // dist 数组初始化为无穷大
	fill(visited, visited + n, false); // 所有节点未被访问
	dist[start] = 0; // 起点的最短路径是 0

	for (int i = 0; i < n; ++i) {
		// 找到当前未访问的节点中，距离最小的节点
		int u = -1;
		for (int j = 0; j < n; ++j) {
			if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
				u = j;
			}
		}

		// 如果当前节点的最短距离仍然是 INF，说明剩余的节点不可达
		if (dist[u] == INF) break;

		// 标记该节点为已访问
		visited[u] = true;

		// 更新与 u 相邻的节点的距离
		for (int v = 0; v < n; ++v) {
			if (!visited[v] && graph[u][v] != INF) {  // 存在边 u -> v
				dist[v] = min(dist[v], dist[u] + graph[u][v]);
			}
		}
	}

	// 输出结果：打印从起点到所有节点的最短路径
	for (int i = 0; i < n; ++i) {
		if (dist[i] == INF) {
			cout << "Node " << i << " is unreachable." << endl;
		}
		else {
			cout << "Shortest distance to node " << i << ": " << dist[i] << endl;
		}
	}
}

```