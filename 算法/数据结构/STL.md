# C++常用容器


## vector, 变长数组，倍增的思想 

### 倍增

**系统为某一程序分配空间时，所需时间与空间大小无关，与申请次数有关**  
因此通过将容量扩大到原来的两倍来优化插入操作，从而在平均情况下保持高效的性能。
#### 时间复杂度分析
插入操作：**O(1)**  
在大多数情况下，插入操作是 O(1)。在扩展时，这一过程的时间复杂度是 O(n)，但由于扩展只在容量满时发生，平均而言，插入操作的时间复杂度依然是 O(1)。  
整体表现：  **O(n)**  
在 n 次插入中，虽然有一些是 O(n) 的复制操作，但由于大多数插入操作是 O(1)，因此整体时间复杂度仍然是 O(n)。  

### 基本操作

    vector<int> a(10,3)// 10个3
    size()  返回元素个数  
    empty()  返回是否为空  
    clear()  清空  
    front()/back()  
    push_back()/pop_back()  
    begin()/end()  
    []  
    支持比较运算，按字典序  

## pair<int, int>  

### 基本操作

    pair<int,string>p;  
    p = make_pair(1,"abc"); p=make_pair(1,abc);
    pair<int,pair<int,int>> p; 可以来储存三个不同的变量
    first, 第一个元素  
    second, 第二个元素  
    支持比较运算，以first为第一关键字，以second为第二关键字（字典序）  

## string，字符串  

### 基本操作

    size()/length()  返回字符串长度  
    empty()  
    clear()  
    substr(起始下标，(子串长度))  返回子串  
    c_str()  返回字符串所在字符数组的起始地址   

## queue, 队列

**先进先出**

### 基本操作

    size()  
    empty()  
    push()  向队尾插入一个元素  
    front()  返回队头元素  
    back()  返回队尾元素  
    pop()  弹出队头元素  
    queue没有clear()函数 想要清空就重新构造一个

## priority_queue, 优先队列，默认是大根堆  

    size()  
    empty()  
    push()  插入一个元素  
    top()  返回堆顶元素  
    pop()  弹出堆顶元素  
    定义成小根堆的方式：priority_queue<int, vector<int>, greater<int>> q;  
    或者 q.push(-x) q.top()=-x

## stack, 栈  

    size()  
    empty()  
    push()  向栈顶插入一个元素  
    top()  返回栈顶元素  
    pop()  弹出栈顶元素  

## deque, 双端队列  

    size()  
    empty()  
    clear()  
    front()/back()  
    push_back()/pop_back()  
    push_front()/pop_front()  
    begin()/end()  
    []  

## set, map, multiset, multimap, 基于平衡二叉树（红黑树），动态维护有序序列  

    size()  
    empty()  
    clear()  
    begin()/end()  
    ++, -- 返回前驱和后继，时间复杂度 O(logn)  

### set/multiset  

**set里面不含重复的元素，multiset可以含重复的元素**

        insert()  插入一个数  
        find()  查找一个数  
        count()  返回某一个数的个数  
        erase()  
            (1) 输入是一个数x，删除所有x   O(k + logn) k是x的个数  
            (2) 输入一个迭代器，删除这个迭代器  
        lower_bound()/upper_bound()
            lower_bound(x)  返回大于等于x的最小的数的迭代器  
            upper_bound(x)  返回大于x的最小的数的迭代器  

### map/multimap  
    
#### 特点

1. 键值对存储，即每个元素是一个pair，first为键，second为值
2. 唯一键：map的键是唯一的，multimap的键可以重复
3. 有序性：自动根据键排序(通常是按升序)

#### 用法

        insert()  插入的数是一个pair  
        erase()  输入的参数是pair或者迭代器  
        find()  
        []  注意multimap不支持此操作。 时间复杂度是 O(logn)  
        lower_bound()/upper_bound()  

## unordered_set, unordered_map, unordered_multiset, unordered_multimap, 哈希表  

    和上面类似，增删改查的时间复杂度是 O(1)  
    不支持 lower_bound()/upper_bound()， 迭代器的++，--  

 ### unordered_map用法

#### 1.简介
- 是一个将key和value关联起来的容器，它可以高效的查找对应的value
- key值应该是唯一的，key和value的数据类型可以不相同
- unordered_map查询单个key的时候效率比map高，但是要查询某一范围内的key值时比map效率低。  
- 可以使用[]操作符来访问key值对应的value值。

#### 2.使用
```C++
unordered_map<string,int> umap; //定义

umap.insert(Map::value_type("test", 1));//增加

//根据key删除,如果没找到n=0
auto n = umap.erase("test")   //删除

auto it = umap.find(key) //改
if(it != umap.end()) 
    it->second = new_value; 


//map中查找x是否存在
umap.find(x) != map.end()//查
//或者
umap.count(x) != 0
```

## bitset, 圧位  

**可以省8倍的空间**
    bitset<10000> s;  
    ~, &, |, ^  
    >>, <<  
    ==, !=  
    []  

    count()  返回有多少个1  

    any()  判断是否至少有一个1  
    none()  判断是否全为0  

    set()  把所有位置成1  
    set(k, v)  将第k位变成v  
    reset()  把所有位变成0  
    flip()  等价于~  
    flip(k) 把第k位取反  

