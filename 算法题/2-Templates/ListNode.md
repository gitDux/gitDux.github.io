# 链表模板

## 返回头节点

对链表做一些操作然后返回链表头节点的题目，经常需要创建一个哨兵节点Dummy，用来记录头节点的位置。

```
剑指Offer 18. 删除链表节点
给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。
```
```cpp
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head->val == val) return head->next;
        ListNode *pre = head, *cur = head->next;
        while(cur != nullptr && cur->val != val) {
            pre = cur;
            cur = cur->next;
        }
        if(cur != nullptr) pre->next = cur->next;
        return head;
    }
};
```