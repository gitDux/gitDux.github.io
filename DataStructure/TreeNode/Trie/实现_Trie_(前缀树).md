# 题目：208.实现 Trie (前缀树)

链接：https://leetcode-cn.com/problems/implement-trie-prefix-tree/

## 描述

> Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

- Trie() 初始化前缀树对象。
- void insert(String word) 向前缀树中插入字符串 word 。
- boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
- boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

## 相关概念

## C++ 代码

```cpp
class Trie {
private:
    vector<Trie*> children; //26 个字母
    bool isend;				//标记是否是单词的结尾

    Trie* searchPrefix(string prefix){
        Trie* node = this;
        for(auto ch : prefix){
            int index = ch - 'a';
            if(node->children[index] == nullptr){
                return nullptr;
            }
            else{
                node = node->children[index];
            }
        }
        return node;
    }

public:
    Trie() {
        children = vector<Trie*>(26);
        isend = false;
    }
    
    void insert(string word) {
        Trie* node = this;
        for(auto ch : word){
            int index = ch - 'a';
            
            if(node->children[index] == nullptr){
                node->children[index] = new Trie();
                node = node->children[index];
            }
            else{
                node = node->children[index];
            }
        }
        node->isend = true;
    }
    
    bool search(string word) {
        Trie* node = searchPrefix(word);
        if(node == nullptr)
            return false;
        else
            return node->isend == true;
    }
    
    bool startsWith(string prefix) {
        return searchPrefix(prefix)? true:false;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

## python 3 代码

```python
class Trie:
    def searchPrefix(self, prefix: str):
        node = self
        for ch in prefix:
            if(node.children[ord(ch)-ord('a')] == None):
                return None
            node = node.children[ord(ch)-ord('a')]
        return node

    def __init__(self):
        self.children = [None]*26
        self.isend = False

    def insert(self, word: str) -> None:
        node = self
        for ch in word:
            if(node.children[ord(ch)-ord('a')] == None):
                node.children[ord(ch)-ord('a')] = Trie()
            node = node.children[ord(ch)-ord('a')]
        node.isend = True


    def search(self, word: str) -> bool:
        node = self.searchPrefix(word)
        if(not node):
            return False
        else:
            return node.isend == True

    def startsWith(self, prefix: str) -> bool:
        return bool(self.searchPrefix(prefix))
```

## 技巧总结

理解为26个分支的树


## 其他

#### [学习链接](https://blog.csdn.net/qq_29996285/article/details/86674779)

#### [208. 实现 Trie (前缀树)](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)

#### [211. 添加与搜索单词 - 数据结构设计](https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/)

#### [307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/)
