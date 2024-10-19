# KMP算法
### 应用
### 算法核心
- 前缀函数的递推求解
- 前缀函数的抽象作用原理
- KMP算法模式匹配优化原理
#### 原理剖析

#### 抽象原理(易于记忆)
 - *求可以使模式串*   **等价位移** *的next数组*
    - 缀不匹配，减短继续，直到为0
    - 匹配成功，j会++
    - 每个next位 ， 被j赋值
 - *利用* **next** *数组实现* **不回溯匹配**
    - 遇到一不等，用next回退 j 减小，直到相等
    - 相等之后，j ++
    - 直到达标，否则 i 加
### 算法模版

- c++模版

```c++
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int KMP(const string & s/*匹配串*/,const string & m/*模式串*/) 
{
	vector<int> next(m.size(), 0);

	//构建next数组
	for (int i = 1, j = 0; i < m.size(); i++)
     {

		//递推找到能匹配的前后缀
		while (j && m[i] != m[j]) j = next[j - 1];
		
		//匹配成功j +1
		if (m[i] == m[j]) j++;
		
		//确定后更新next 
		next[i] = j;
	}


	//KMP匹配
	for (int i = 0, j = 0; i < s.size(); i++) 
    {
		
		//根据next回退
		while (j && s[i] != m[j]) j = next[j - 1];

		//正常匹配
		if (s[i] == m[j]) j++;
		
		//检测当前匹配情况
		if (j == m.size()) return i - j + 1;
	}

}

int main() {
	cout << KMP("dsadwqfsefdfsdfessf", "fdf");
	return 0;
}
```
输出:   **9** 
#### 代码剖析