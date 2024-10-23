


### 代码模版
```c++
#include <stdio.h>
#include <ctype.h>  // 提供 isdigit() 函数

void read(int* x) {
    *x = 0;             // 初始化为 0
    int f = 1;          // 符号位，默认正数
    char ch = getchar(); // 读取第一个字符

    // 跳过所有非数字字符（包括空白符）
    while (ch != '-' && !isdigit(ch)) {
        if (ch == EOF) return;  // 遇到 EOF 立即返回
        ch = getchar();
    }

    // 检查是否为负数
    if (ch == '-') {
        f = -1;
        ch = getchar();  // 继续读取下一个字符
    }

    // 读取数字部分
    while (isdigit(ch)) {
        *x = *x * 10 + (ch - '0');  // 更新数值
        ch = getchar();
    }

    *x *= f;  // 根据符号位调整正负
}

```