```c++
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // 表示无穷大

struct Edge {
    int to, weight;
};

vector<int> dijkstra(int start, const vector<vector<Edge>>& graph) {
    int n = graph.size(); // 图的节点数
    vector<int> dist(n, INF); // 存储每个节点到起点的最短距离
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 最小堆

    dist[start] = 0; // 起点距离为0
    pq.push({0, start}); // 将起点加入优先队列

    while (!pq.empty()) {
        int d = pq.top().first; // 当前最小距离
        int u = pq.top().second; // 当前节点
        pq.pop();

        // 如果当前距离大于已知最短距离，跳过
        if (d > dist[u]) continue;

        // 遍历邻接节点
        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            // Relaxation
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v}); // 更新最短距离并加入优先队列
            }
        }
    }

    return dist; // 返回到各节点的最短距离
}

int main() {
    int n, m; // n是节点数，m是边数
    cin >> n >> m;

    vector<vector<Edge>> graph(n); // 图的邻接表

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // 输入边的起点、终点和权重
        graph[u].push_back({v, w}); // 添加边
        graph[v].push_back({u, w}); // 如果是无向图
    }

    int start; // 起点
    cin >> start;

    vector<int> shortest_distances = dijkstra(start, graph);

    // 输出每个节点到起点的最短距离
    for (int i = 0; i < n; ++i) {
        if (shortest_distances[i] == INF) {
            cout << "Node " << i << ": INFINITY" << endl;
        } else {
            cout << "Node " << i << ": " << shortest_distances[i] << endl;
        }
    }

    return 0;
}

```