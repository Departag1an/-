// 题目
// https://kamacoder.com/problempage.php?pid=1182

#include <bits/stdc++.h>
using namespace std;
#define fast ios ::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl '\n'
typedef long long ll;
#define MAX_INT ll(2e64 - 1)
#define REP(i, s, e) for (int i = (s); i < (e); ++i)
#define OUT(v) for (int k = 0; k < v.size(); ++k) cout << v[k] << ' '; cout << endl;
const int N = 1e5 + 10;

vector<int> in(1100);
vector<vector<int>> g;

void init(vector<int>& father) {
    for (int i = 0; i < father.size(); i++) {
        father[i] = i;
    }
}

int find(int u, vector<int>& father) {  // 返回根节点
    return u == father[u] ? u : father[u] = find(father[u], father);
}
bool join(int a, int b, vector<int> &father) {
    a = find(a, father);
    b = find(b, father);
    if (a == b) return false;
    father[b] = a;
    return true;
}
bool isSame(int a, int b, vector<int>& father) {
    a = find(a, father);
    b = find(b, father);
    return a == b;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        in[b]++;
        g.push_back({a, b});
    }
    // 找到一个边(a, b) a的入度不为0, 删除a, b后, 仅有一个根节点, 并且没有环
    for (int i = n - 1; i >= 0; i--) {
        vector<int> father(1100);
        vector<int> tin(1100, 0);
        init(father);
        bool status = true;
        if (in[g[i][0]]) {  // a的入度不为0
            for (int j = 0; j < n; j++) {
                int a = g[j][0], b = g[j][1];
                if (j != i) {
                    tin[b]++;
                    if (!join(a, b, father)) {
                        status = false;
                        break;
                    }
                }
            }
            if (status) { // 没有环
                int cnt = 0;
                for (int i = 1; i <= n; i++) {
                    if (tin[i] == 0) cnt++;
                }
                if (cnt == 1) {
                    cout << g[i][0] << ' ' << g[i][1];
                    return 0;
                }
            }
        }
    }
    
    return 0;
}
