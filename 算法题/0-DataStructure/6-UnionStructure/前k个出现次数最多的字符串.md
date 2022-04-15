

# [692. 前K个高频单词](https://leetcode-cn.com/problems/top-k-frequent-words/)

- 给一非空的单词列表，返回前 *k* 个出现次数最多的单词。

- 返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率，按字母顺序排序。

本题有两种方法：

- 哈希表加排序
  - 时间复杂度：$O(l \times n + l \times m \log m)$，其中 $n$ 表示给定字符串序列的长度，$l$表示字符串的平均长度，$m$ 表示实际字符串种类数。我们需要 $l \times n$ 的时间将字符串插入到哈希表中，以及 $l \times m \log m$ 的时间完成字符串比较（最坏情况下所有字符串出现频率都相同，我们需要将它们两两比较）。
  - 空间复杂度：$O(l \times m)$，其中 $l$ 表示字符串的平均长度，$m$ 表示实际字符串种类数。哈希表和生成的排序数组空间占用均为 $O(l \times m)$。
- 哈希表加小顶堆
  - 时间复杂度：$O(l \times n + l \times m \log k)$
  - 空间复杂度：$O(l \times (m+k))$

使用 `c++` 的 `priority_queue` 实现堆的操作

```cpp
class Solution {
public:
    typedef pair<string,int> PIS;
    vector<string> topKFrequent(vector<string>& words, int k) {
        // 建立并填充哈希表
        unordered_map<string,int> mp;
        for(auto& word : words){
            if(mp.count(word)) mp[word] += 1;
            else mp[word] = 1;
        }
        
        // 自定义比较规则
        auto comp = [](PIS A,PIS B){
            return A.second==B.second? A.first<B.first:A.second>B.second;
        };
		// 定义并维护一个长度为k的堆， 这里提供两种遍历unordered_map的方式
        priority_queue<PIS,vector<PIS>,decltype(comp)> pq(comp);
        for(auto &kv:mp){
            pq.push(kv);
            if(pq.size()>k) pq.pop();
        }
        // unordered_map<string,int>::iterator it = mp.begin();
        // while(it!=mp.end()){
        //     pq.push(*it);
        //     if(pq.size()>k){
        //         pq.pop();
        //     }
        //     it++;
        // }
        
        // 反转一些 输出答案
        vector<string> ans(k);
        while(!pq.empty()) {
            ans[--k] = pq.top().first;
            pq.pop();
        }
        return ans;
    }
};
```

