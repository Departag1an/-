#ifndef CODE_H
#define CODE_H

#include <cstdio>
#include <vector>
#include <iostream>
#include <cctype>
#include <stack>
#include <queue>
#include <string>
#include <list>
#include <array>
#include <set>
#include <utility>
#include <map>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

#define I_ERROR -9999
#define Oend printf("\n");
#define Ospace printf(" ");
#define Opoint printf(".");
#define LOut(vec) {for(int i = 0 ; i < vec.size()-1;i++){cout<<vec[i]<<" ";}cout<<vec[vec.size()-1]<<endl;} 
#define LIn(vec){int t = 0;while (t < vec.size()) vec[t++] = in();}
#define REP(it,start,end,step) for (size_t it = start ; it <end;it+=step )
#define TIE {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);}


namespace Debug {
    template<typename T>
    void debug(const T& container) {
        for (const auto& e : container) {
            cout << e << " ";
        }
        cout << endl;
    }


    template<typename K, typename V>
    void debug(const std::map<K, V>& mp) {
        for (const auto& e : mp) {
            cout << e.first << ": " << e.second << " ";
        }
        cout << endl;
    }

    template<typename K, typename V>
    void debug(const std::unordered_map<K, V>& umap) {
        for (const auto& e : umap) {
            cout << e.first << ": " << e.second << " ";
        }
        cout << endl;
    }

    template<typename T1, typename T2>
    void debug(const std::pair<T1, T2>& p) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

   
    template<typename T1, typename T2, typename T3>
    void debug(const std::tuple<T1, T2, T3>& t) {
        cout << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")" << endl;
    }

    template <typename T, typename N>
    void debug(T* arr, N n) {
        for (N i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}


namespace IO {
    int in() {
        int f = 1;
        char chace = getchar();
        int res = 0;
        while (chace - '0' < 0 || chace - '9' > 0) {
            if (chace == EOF || chace == '\n0') return I_ERROR;
            if (chace == '-') {
                f = -1;
                chace = getchar();
                break;
            }
            chace = getchar();
        }
        if (chace == '-') {
            return I_ERROR;
        }
        while (chace - '0' >= 0 && chace - '9' <= 0) {
            res = res * 10 + chace - '0';
            chace = getchar();
        }
        res *= f;
        return res;
    }

    void out(int x) {
        if (x < 0) x = -x;
        if (x < 10) putchar(x + '0');
        else {
            out(x / 10), putchar(x % 10 + '0');
        }
    }
}

// 排序相关
namespace Sorting {
    int tem[100]; // 临时数组，用于归并排序

    void quick_sort(int q[], int l, int r) {
        if (l >= r) return;
        int x = q[l], i = l - 1, j = r + 1;
        while (i < j) {
            do i++; while (q[i] < x);
            do j--; while (q[j] > x);
            if (i < j) swap(q[i], q[j]);
        }
        quick_sort(q, l, j);
        quick_sort(q, j + 1, r);
    }

    void merge_sort(int q[], int l, int r) {
        if (l >= r) return;
        int mid = l + r >> 1;
        merge_sort(q, l, mid);
        merge_sort(q, mid + 1, r);
        int k = 0, i = l, j = mid + 1;
        while (i <= mid && j <= r) {
            if (q[i] < q[j]) tem[k++] = q[i++];
            else tem[k++] = q[j++];
        }
        while (i <= mid) tem[k++] = q[i++];
        while (j <= r) tem[k++] = q[j++];
        for (i = l, j = 0; i <= r; i++, j++) q[i] = tem[j];
    }
}


namespace KMP {
    void getNext(char* pattern, int pattern_size, int* next) {
        next[0] = 0;
        for (int i = 1, j = 0; i < pattern_size; i++) {
            while (j > 0 && pattern[i] != pattern[j]) j = next[j - 1];
            if (pattern[i] == pattern[j]) j++;
            next[i] = j;
        }
    }

    int KMP(int* next, char* pattern, int pattern_size, char* text, int text_size) {
        for (int i = 0, j = 0; i < text_size; i++) {
            while (j > 0 && pattern[j] != text[i]) j = next[j - 1];
            if (pattern[j] == text[i]) j++;
            if (j == pattern_size) return i - j + 1;
        }
        return -1;
    }
}



#endif
using namespace Debug;
void slove() {




}
int main() {
    TIE;
    return 0;
}
