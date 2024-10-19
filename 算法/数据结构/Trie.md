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



