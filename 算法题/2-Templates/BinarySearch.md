## [题目列表](https://blog.csdn.net/sinat_33641359/article/details/79064155)

- [34] Search for a Range
- [35] Search Insert Position
- [74] Search a 2D Matrix
- [240] Search a 2D Matrix II
- 278、1a62、26、80、88、4、151

## 框架

```cpp
int BinarySearch(vector<int> nums, int target) {
    int left = 0, right = ...;

    while (...) {
        int mid = (left + right) / 2; //可以换成 int mid = left + (right-right) / 2 防止溢出
        if (nums[mid] == target) { // 等号写前面
            ...;
        } else if (nums[mid] < target) {
            left = ...;
        } else if (nums[mid] > target) {
            right = ...;
        }
    }
    return ...;
}
```

## 例题：[34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

给定一个按照升序排列的整数数组 `nums`，和一个目标值 `target`。找出给定目标值在数组中的开始位置和结束位置。如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

进阶：你可以设计并实现时间复杂度为 `O(log n)`的算法解决此问题吗？

思路：先二分查找，再在从找到的点展开

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // 防空
        if(!nums.size()){
            return {-1,-1};
        }

        // 二分查找参数初始化
        int l = 0;
        int r = nums.size()-1;	// point 1
        int cur = 0;

		// 二分查找while循环阶段
        // 这里有四点需要注意
        while(l<=r){ // point 2
            cur = (l+r+1)>>1; //向上取整 //point 3
            if(nums[cur]==target){
                break;
            }
            else if(nums[cur]>target) r = cur - 1; //point 4
            else l = cur + 1;						//point 5
        }
        // 后处理
        if(nums[cur] == target){
            l = cur;
            r = cur;
            while(l>0&&nums[l-1]==target){
                l--;
            }
            while(r<nums.size()-1&&nums[r+1]==target){
                r++;
            }
            return {l,r};
        }
        else{
            return {-1,-1};
        }

    }
};
```

模板提炼：在数组中查找一个目标数字

```cpp
int binarySearch(vector<int>& nums, int target) {
    // 防空
    if(!nums.size()){
        return -1;
    }
    // 二分查找参数初始化
    int l = 0;
    int r = nums.size()-1;	// point 1
    int cur = 0;
    // 二分查找while循环阶段
    // 这里有四点需要注意
    while(l<=r){ // point 2
        cur = (l+r+1)>>1; //向上取整 //point 3
        if(nums[cur]==target) break;
        else if(nums[cur]>target) r = cur - 1; //point 4
        else l = cur + 1;						//point 5
    }
    // 后处理阶段
    if(nums[cur] == target)	return cur;
    else return -1;

```

## 测试题 [35. 搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // 防空
        if(!nums.size()){
            return 0;
        }
        // 二分查找参数初始化
        int l = 0;
        int r = nums.size()-1;	// point 1
        int cur = 0;
        // 二分查找while循环阶段
        // 这里有四点需要注意
        while(l<=r){ // point 2
            cur = (l+r+1)>>1; //向上取整 //point 3
            if(nums[cur]==target) break;
            else if(nums[cur]>target) r = cur - 1; //point 4
            else l = cur + 1;						//point 5
        }
        cout<<cur<<endl;
        // 后处理阶段
        // 最后的cur要么找到了
        // 要么在目标位置的旁边
        // 如果cur指向的值大于目标值，说明要在当前位置放置目标值，而包括该位置的向右的所有元素右移一格
        // 如果cur指向的值小于目标值，说明要在当前位置右边放置目标值，cur+1;
        return (nums[cur]>=target)? cur:cur+1;
    }
};
```
