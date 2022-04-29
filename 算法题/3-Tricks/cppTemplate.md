## ListNode

### 单链表定义

```cpp

struct ListNode
{
    int val;
    ListNode* next;
    ListNode():val(-1),next(nullptr){}
    ListNode(int _val):val(_val){next = nullptr;}
    ListNode(int _val,ListNode* _next):val(_val),next(_next){}
};
```

### 从数组vector建立链表

```cpp
ListNode* buildListNode(std::vector `<int>` nums){
    ListNode* dummyNode = new ListNode(-1);
    ListNode* cur = dummyNode;
    for(int num :nums){
        ListNode* nex = new ListNode(num);
        cur->next = nex;
        cur = nex;
    }
    return dummyNode->next;
}
```

### 判断链表是否有环

```cpp
bool hasCircle(ListNode* head){
    ListNode *slow, *fast;
    slow = head;
    fast = head;

    while(fast&&fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            return true;
        }
    }
    return false;
}
```

### 判断带环链表的入口节点

```cpp
ListNode* findEnterNode(ListNode* head){
    ListNode *slow, *fast;
    slow = head;
    fast = head;

    while(fast&&fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            break;
        }
    }
    fast = head;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
```

### 打印链表所有值

```cpp
void showListNode(ListNode* head){
    ListNode* cur = head;
    while(cur){
        std::cout<`<cur->`val;
        if(cur->next)
            std::cout<<"->";
        cur = cur->next;
    }
    std::cout<<std::endl;
    return;
}
```
