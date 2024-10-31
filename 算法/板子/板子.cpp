#ifndef Code
#define Code 
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

// 通用调试函数
template<typename T>
void debug(const T & container) {
	for (const auto& e : container) {
		cout << e << " ";
	}
	cout << endl;
}

// 特化调试函数用于 map 和 unordered_map
template<typename K, typename V>
void debug(const std::map<K, V>&mp) {
	for (const auto& e : mp) {
		cout << e.first << ": " << e.second << " ";
	}
	cout << endl;
}

template<typename K, typename V>
void debug(const std::unordered_map<K, V>&umap) {
	for (const auto& e : umap) {
		cout << e.first << ": " << e.second << " ";
	}
	cout << endl;
}

// 特化调试函数用于 pair
template<typename T1, typename T2>
void debug(const std::pair<T1, T2>&p) {
	cout << "(" << p.first << ", " << p.second << ")" << endl;
}

// 特化调试函数用于 tuple（不使用 C++17 的 std::apply）
template<typename T1, typename T2, typename T3>
void debug(const std::tuple<T1, T2, T3>&t) {
	cout << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")" << endl;
}

// 特化调试函数用于数组
template<typename T, size_t N>
void debug(const T(&arr)[N]) {
	for (const auto& e : arr) {
		cout << e << " ";
	}
	cout << endl;
}
int in() {
	int f = 1;
	char chace = getchar();
	int res = 0;
	while (chace - '0' < 0 || chace - '9' > 0) {
		if (chace == EOF || chace == '\n0')return I_ERROR;
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
	if (x < 0)x = -x;
	if (x < 10)putchar(x + '0');
	else {
		out(x / 10), putchar(x % 10 + '0');
	}
}


//kmp

void getNext(char *pattern,int pattern_size,int * next) {
	next[0] = 0;
	for (int i = 1, j = 0; i < pattern_size; i++)
	{
		while (j > 0 && pattern[i] != pattern[j])j = next[j - 1];
		if (pattern[i] == pattern[j])j++;
		next[i] = j;
	}
}
int KMP(int* next, char* pattern, int pattern_size, char* text, int text_size)
{
	for (int i = 0, j = 0; i < text_size; i++) {
		while (j > 0 && pattern[j] != text[i])j = next[j - 1];
		if (pattern[j] == text[i])j++;
		if (j == pattern_size)return i - j + 1;
	}
	return -1;
}



//Trie
#define n 1000
int son[n][26], cnt[n], idx;
void insert(char* str) {
	int p = 0;
	for (int i = 0; str[i]; i++) {
		int u = str[i] - 'a';
		if (!son[p][u]) son[p][u] = ++idx;
		p = son[p][u];
	}
	cnt[p]++;
}
int find(char* str) {
	int p = 0;
	for (int i = 0; str[i]; i++) {
		int u = str[i] - 'a';
		if (!son[p][u]) return 0;
		p = son[p][u];
	}
	return cnt[p];
}



//bit enum
#include<iostream>//子集枚举
void TravalBool(int x) {
	for (int i = 0; i < x; i++) {
		for (int p = 0; p < 31; p++) {
			if (i & (1 << p)) {
				std::cout << '1';
			}
			else {
				std::cout << '0';
			}
		}
		std::cout << std::endl;
	}
}
//

#endif

int main() 	
{
	TIE;
	

	return 0;
}