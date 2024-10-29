# Trie(字典数)

## 定义：高效地存储和查找字符串集合的数据结构

## 模板

```C++
int son[N][26], cnt[N], idx;

// 0号点既是根节点，又是空节点
// son[][]存储树中每个节点的子节点
// cnt[]存储以当前节点结尾的单词数量
// idx是节点编号

// 插入一个字符串
void insert(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++; // 当前节点单词数量加一
}
// 查询字符串出现的次数
int query(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p];
}
```

## 分析

idx是节点编号,从0开始,在创建新节点时递增。


## 例题

### 最大异或和  

在给定的整数数组中，找到两个数，使得它们的异或值最大，并输出这个最大值。  
输入格式:第一行输入一个整数N:第二行输入N个整数。  
输出格式：输出一个整数，表示答案。

```C++
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int n;
int a[N];
int son[N * 31][2], idx;

void insert(int x)
{
    int p = 0;
    for (int i = 30; i >= 0; i--)
    {
        int u = x >> i & 1;
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
    }
}

int query(int x)
{
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--)
    {
        int u = x >> i & 1;
        if (son[p][!u])
        {
            res = res * 2 + !u;
            p = son[p][!u];
        }
        else
        {
            res = res * 2 + u;
            p = son[p][u];
        }
    }
    return res;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        insert(a[i]);
        res = max(res, query(a[i]));
    }
    cout << res << endl;
    return 0;

        }
```
