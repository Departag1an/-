# DFS 算法

## 算法描述
- DFS的核心是**分枝搜索，策略性回溯，递归性解决**
- DFS是路径算法的主干，另外还有一些常伴随出现的技巧

## 适用性
- 这个算法没有在搜索过程中进行剪枝，因此得到的路径只具有一般的特征
- 如需要得到最短路径等等特性路径，需要对搜索树进行剪枝，但效率不高
- 适合寻找全集联通路径
  
## 数据结构选择
- 图的邻接表  \( 稀疏图\)、的邻接矩阵 \(稠密图\)
- 栈
- 路径vector

## 算法模板
* 可达性
```C++
#include <stack>
#include <set>
#include <iostream>
#include <vector>
using namespace std;

const int RowMax = 1e3 + 5; // 行最大值
const int ColumnMax = 1e3 + 5; // 列最大值
#define INIT 0 // 初始值

// 地图
int Map[RowMax][ColumnMax] = { INIT };
set<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 深度优先搜索函数
int BFS(int Map[RowMax][ColumnMax], int sx, int sy, int ex, int ey, int rows, int columns) {
    stack<pair<int, int>> s; // 用于存储待处理的位置
    set<pair<int, int>> visited; // 记录已访问的位置

    pair<int, int> start = { sx, sy };
    s.push(start);
    visited.insert(start);

    while (!s.empty()) {
        pair<int, int> current = s.top();
        s.pop();

        // 检查是否到达目标位置
        if (current.first == ex && current.second == ey) {
            cout << "YES" << endl;
            return 1;
        }

        // 扩展相邻位置
        for (const auto& dir : directions) {
            int newX = current.first + dir.first;
            int newY = current.second + dir.second;

            // 检查位置是否合法
            if (newX >= 0 && newX < rows && newY >= 0 && newY < columns) {
                pair<int, int> newPos = { newX, newY };
                if (visited.find(newPos) == visited.end() && Map[newX][newY] == 0) {
                    s.push(newPos);
                    visited.insert(newPos); // 标记为已访问
                }
            }
        }
    }

    cout << "NO" << endl; // 如果没有找到路径
    return 0;
}

int main() {
    int r, c;
    int sx, sy, ex, ey;
    cin >> r >> c;
    cin >> sx >> sy >> ex >> ey;

    // 输入地图
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> Map[i][j];
        }
    }

    // 执行 DFS
    DFS(Map, sx, sy, ex, ey, r, c);
    return 0;
}

```
- 求路径