
#### 前言:

##### 创作背景: 
2024-11-16日xx贺被蓝桥杯模拟赛的某道日期题目恶心坏了,
于是连夜手搓了这个遍历日期的板子, (纯代码15行), 毕竟咱和python还是比不了
##### OS:
我觉得罪魁祸首是每个月的天数不同, 真该死啊, 要是每个月都是30天就好了
##### 代码功能:
给定起始日期和结束日期, 能够遍历得到区间内每一天的日期
```C++
#include <bits/stdc++.h>
using namespace std;
#define fast ios ::sync_with_stdio(false), cin.tie(0), cout.tie(0)
typedef long long ll;
#define MAX_INT int(2e31 - 1)
const int N = 1e5 + 10;

int rq[13] = {29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // r[2]平年, rq[0] 是闰年
bool check(int yy) { // 闰年判断函数, 是则返回true
    return ((yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0));
}
int main() {
    int yy = 2023, mm = 12, dd = 1; // 起始日期
    int YY = 2024, MM = 12, DD = 31; // 结束日期
    while(true) {
        printf("%d-%02d-%02d\n", yy, mm, dd); // 此处写日期处理的代码, 记得写上面, 不能写下面不然会少判断第一天
        if (yy == YY && mm == MM && dd == DD) break; // 不能把while的true换成这个, 不然最后一天遍历不到
        if ( (!check(yy) && dd == rq[mm]) || (check(yy) && mm == 2 ? dd == rq[0] : dd == rq[mm])) { // 日期和月份进位
            dd = 1, mm++;
            if (mm > 12) mm = 1, yy++;
        }
        else dd++;
    }
    return 0;
}
```
