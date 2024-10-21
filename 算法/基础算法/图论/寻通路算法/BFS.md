 # BFS算法
 

## 算法描述
- 算法原理可参考波的传递，圆在变大时第一个进入圆内的点一定距离圆心最近，因此可以用BFS算法来寻找最短路径。
  



## 算法步骤
## 算法模板
```C++
#include <queue>
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

// 广度优先搜索函数
int BFS(int Map[RowMax][ColumnMax], int sx, int sy, int ex, int ey, int rows, int columns) {
    queue<pair<int, int>> q; // 队列用于存储待处理的位置
    set<pair<int, int>> visited; // 记录已访问的位置

    pair<int, int> start = { sx, sy };
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

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
                    q.push(newPos);
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

    // 执行 BFS
    BFS(Map, sx, sy, ex, ey, r, c);
    return 0;
}

```