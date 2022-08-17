
next数组定义

next[i] 表示原字符串和目标字符串在第 i 个位置发生未匹配情况是，0~i-1这一段上前后缀相同长度。

AABAAC：001012


```cpp
class Solution {
public:
    vector<int> getNext(string needle){
        vector<int> next(needle.size());
        int i=1;
        int j =0;
        while(i< needle.size()-1){
            if(j==0 && needle[i] != needle[j]) next[++i] = 0;
            else if(needle[i] == needle[j]) next[++i] = ++j;
            else j = next[j]; 
        }
        return next;
    }
    int strStr(string haystack, string needle) {
        if(needle == "") return 0;
        vector<int> next = getNext(needle);
        int i = 0;
        while(i < haystack.size()){
            int j=0;
            while(i < haystack.size() && j < needle.size() && haystack[i] == needle[j]){
                i++;
                j++;
            }
            if(j == needle.size()) return i-j;
            i = next[j] ? i- next[j]:i-j+1;
        }
        return -1;
    }
   
};
```
