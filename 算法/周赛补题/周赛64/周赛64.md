# 周赛64  https://ac.nowcoder.com/acm/contest/92662

## E 小红的字符串重排
### https://ac.nowcoder.com/acm/contest/92662/E

```C++
#include<bits/stdc++.h>
using namespace std;
string s;

int main()
{
    ios::sync_with_stdio(0),cin.tie(); 
    cin>>s;
    vector<pair<char,int>> a(s.size());
    string ans(s.size(), ' ');
    int cnt[500];
    memset(cnt,0,sizeof(cnt));
    int mx=0;
    for(int i=0;i<s.size();i++)
    {
        a[i].first=s[i],a[i].second=i;
        cnt[s[i]-'a']++;
        mx=max(mx,cnt[s[i]-'a']);
    }
    if(mx>s.size()/2)
    {
        cout<<-1<<endl;
        return 0;
    }
    sort(a.begin(),a.end(),[](const pair<char,int>&a1,const pair<char , int >&a2)
         {return a1.first<a2.first;});
    for(int i=0;i<s.size();i++)
    {
        ans[a[i].second]=a[(i+mx)%s.size()].first;
        
    }
     cout << ans << endl;
    return 0;
}

```

## 思路
1. 首先统计每个字母出现的次数，如果出现次数大于等于字符串长度的一半，则返回-1
2. 将字符串中的字母和下标存储到数组中，并按照字母排序
3. 遍历数组，将每个字母替换为距离它最远的字母，即下标为 **(i+mx)%s.size()** 的字母
4. 输出结果

# F小红的树上路径查询（easy）https://ac.nowcoder.com/acm/contest/92662/F

