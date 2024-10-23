


### 代码模版
```c++#include <stdio.h>
#include <ctype.h>  // 提供 isdigit() 函数

int read(int* x) {
    *x = 0;             // 初始化为 0
    int f = 1;          // 符号位，默认正数
    char ch = getchar(); // 读取第一个字符

    // 跳过所有非数字字符（包括空白符）
    while (ch != '-' && !isdigit(ch)) {
        if (ch == EOF) return 0;  // 遇到 EOF 返回 0 表示失败
        ch = getchar();
    }

    // 检查是否为负数
    if (ch == '-') {
        f = -1;
        ch = getchar();  // 继续读取下一个字符
    }

    // 如果 `-` 后没有数字，返回失败
    if (!isdigit(ch)) return 0;

    // 读取数字部分
    while (isdigit(ch)) {
        *x = *x * 10 + (ch - '0');  // 更新数值
        ch = getchar();
    }

    *x *= f;  // 根据符号位调整正负
    return 1; // 返回 1 表示成功
}

int main() {
    int x;
    if (read(&x)) {
        printf("输入的数字是: %d\n", x);
    } else {
        printf("输入无效\n");
    }

    return 0;
}


```