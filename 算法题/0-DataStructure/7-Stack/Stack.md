## 单调栈

单调栈何时用：为任意一个元素找左边和右边第一个比自己大/小的位置用单调栈.

https://blog.csdn.net/qq_59144780/article/details/122787827

[最大矩形面积](https://leetcode.cn/problems/0ynMMM/)

![单调栈](https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fpic1.zhimg.com%2Fv2-78b7485b4035ed31c8951fe0fedd8efe_1440w.jpg%3Fsource%3D172ae18b&refer=http%3A%2F%2Fpic1.zhimg.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=auto?sec=1658564940&t=e4fa12927852f2247450273f01399588#pic_center)

![图片](https://assets.leetcode.com/uploads/2021/01/04/histogram.jpg#pic_center)

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> stk;
        int ans=INT_MIN;
        for(int i = 0; i < heights.size();i++){
            while(!stk.empty()&& heights[stk.top()] >= heights[i]){
                int top = stk.top(); stk.pop();
                ans = max(ans,heights[top]*(stk.empty()?i:(i-stk.top()-1)));
            }
            stk.push(i);
        }
        return ans;
    }
};
```
