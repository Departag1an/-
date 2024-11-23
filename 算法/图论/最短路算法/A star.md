

# A* 算法(未完善)
`A*`算法实际上是Dijkstra算法的一种改进，它在选择下一个要扩展的节点时，不仅考虑了从起点到当前节点的实际代价（记为`g`），还考虑了一个启发式估计值（记为`h`），该估计值是从当前节点到目标节点的估计代价。因此，`A*`算法的每次扩展选择的是`f(n) = g(n) + h(n)`值最小的节点。

## 基本步骤 
1. 初始化：将起点加入到开放列表,并设置其`g`值为0，`h`值为从起点到终点的启发式估计值。
2. 循环：当开放列表不为空时，执行以下步骤：
   - 从开放列表中取出`f`值最小的节点作为当前节点。
   - 如果当前节点是目标节点，则算法结束，返回路径。
   - 否则，将当前节点从开放列表移动到关闭列表。对于当前节点的每一个邻居节点，执行以下步骤：
     - 如果邻居节点已经在关闭列表中，则跳过该邻居节点。
     - 计算从起点经过当前节点到达邻居节点的代价`g`值。
     - 如果邻居节点不在开放列表中，或者计算出的`g`值小于邻居节点在开放列表中的`g`值，则更新邻居节点的`g`值，并设置其`h`值为从邻居节点到终点的启发式估计值，然后将邻居节点加入到开放列表。
3. 如果开放列表为空且未找到目标节点，则算法结束，返回失败。

## 启发式函数
启发式函数`h(n)`的选择对`A*`算法的性能有很大影响。常见的启发式函数包括：
- 曼哈顿距离：适用于网格图，计算两个点在水平和垂直方向上的距离之和。
- 欧几里得距离：适用于平面图，计算两个点之间的直线距离。
- 对角线距离：适用于网格图，计算两个点之间的最短路径长度，允许对角线移动。


### 无权图
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring> // 用于 memset
#include <functional> // 用于自定义函数
#include <utility> // 用于 pair

using namespace std;

const int MAXN = 510;   // 根据题目需求调整最大网格大小
const int INF = 0x3f3f3f3f;

// 定义方向数组（上下左右）
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 节点结构体
struct Node {
    int x, y;        // 节点的坐标
    int g, h;        // g 为起点到当前点的代价，h 为启发式估计
    int f() const { return g + h; } // 总代价 f = g + h

    // 优先队列需要的比较运算符，按 f 值升序排列
    bool operator<(const Node& other) const {
        return f() > other.f(); // 小根堆
    }
};

// 判断坐标是否在网格范围内
inline bool isValid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// A* 主函数
int a_star(int n, int m, vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end, function<int(int, int)> heuristic) {
    priority_queue<Node> pq; // 小根堆
    vector<vector<int>> dist(n, vector<int>(m, INF)); // 距离表

    // 起点初始化
    int sx = start.first, sy = start.second;
    int ex = end.first, ey = end.second;
    pq.push({sx, sy, 0, heuristic(sx, sy)});
    dist[sx][sy] = 0;

    // 主循环
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int x = cur.x, y = cur.y;

        // 如果到达终点
        if (x == ex && y == ey) return cur.g;

        // 扩展邻居节点
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (!isValid(nx, ny, n, m) || grid[nx][ny] == 1) continue; // 不合法或障碍物

            int new_g = cur.g + 1; // 假设每次移动的代价为 1
            if (new_g < dist[nx][ny]) {
                dist[nx][ny] = new_g;
                pq.push({nx, ny, new_g, heuristic(nx, ny)});
            }
        }
    }

    return -1; // 无法到达终点
}

int main() {
    // 输入网格大小
    int n, m;
    cin >> n >> m;

    // 输入网格（0 为可走，1 为障碍物）
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // 起点和终点坐标
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;

    // 启发式函数（曼哈顿距离）
    auto heuristic = [&](int x, int y) {
        return abs(x - ex) + abs(y - ey);
    };

    // 调用 A* 算法
    int result = a_star(n, m, grid, {sx, sy}, {ex, ey}, heuristic);

    if (result == -1) cout << "impossible" << endl;
    else cout << result << endl;

    return 0;
}
```


### 非负权图


---

### 不同启发函数对性能的影响

| 启发函数            | 准确性          | 性能影响              |
|---------------------|----------------|-----------------------|
| 几何距离（准确）      | 高            | 探索节点最少，效率高     |
| 拓扑距离 + 最小权值     | 中等           | 比较保守，探索更多节点     |
| 启发函数为零（Dijkstra）| 最低           | 无启发作用，退化为 Dijkstra |



### 总结

- **核心**：启发函数的设计要结合图的权值特性和问题场景。
- **启发函数技巧**：
  1. 如果有几何信息，用距离结合最小权值。
  2. 如果无几何信息，用拓扑距离估算代价。
  3. 利用问题领域的特定规则或上下文知识。
- **关键目标**：保持启发函数可接受（保证最优解）并尽量准确（提高效率）。
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 510; // 根据题目调整最大节点数
const int INF = 0x3f3f3f3f;

// 节点结构体
struct Node {
    int id;   // 当前节点的编号
    int g, h; // g 为起点到当前点的代价，h 为启发式估计值
    int f() const { return g + h; } // 总代价 f = g + h

    bool operator<(const Node& other) const {
        return f() > other.f(); // 小根堆
    }
};

// A* 主函数
int a_star(int n, vector<vector<pair<int, int>>>& graph, int start, int end, function<int(int)> heuristic) {
    priority_queue<Node> pq; // 小根堆
    vector<int> dist(n + 1, INF); // 距离表，初始化为无穷大

    // 起点初始化
    pq.push({start, 0, heuristic(start)});
    dist[start] = 0;

    // 主循环
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.id;

        // 如果到达终点
        if (u == end) return cur.g;

        // 扩展当前节点的所有邻居
        for (auto [v, w] : graph[u]) {
            int new_g = cur.g + w; // 当前节点到邻居节点的代价
            if (new_g < dist[v]) {
                dist[v] = new_g;
                pq.push({v, new_g, heuristic(v)});
            }
        }
    }

    return -1; // 无法到达终点
}

int main() {
    int n, m; // 节点数和边数
    cin >> n >> m;

    // 邻接表存图，graph[u] 存储从 u 出发的所有邻居 (v, w)
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        // 如果是无向图，则同时加入反向边
        // graph[v].emplace_back(u, w);
    }

    // 起点和终点
    int start, end;
    cin >> start >> end;

    // 启发式函数（假设节点编号与目标节点的关系可用自定义距离计算）
    auto heuristic = [&](int u) -> int {
        // 示例：启发式为 0（即退化为 Dijkstra 算法）
        return 0; // 替换为问题特定的启发式函数
    };

    // 调用 A* 算法
    int result = a_star(n, graph, start, end, heuristic);

    if (result == -1) cout << "impossible" << endl;
    else cout << result << endl;

    return 0;
}
```