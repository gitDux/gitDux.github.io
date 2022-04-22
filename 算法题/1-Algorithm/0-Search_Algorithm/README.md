

# 搜索算法分类：

- DFS 深度优先搜索

- BFS 广度优先搜索

- 双向广度优先搜索
- 启发式搜索
- A* 算法
- 迭代加深搜索
- IDA*
- 回溯法
- Dancing Links
- Alpha-Beta剪枝
- DFS 优化剪枝
  - 最常用的剪枝有三种，记忆化搜索、最优性剪枝、可行性剪枝。

## A*算法

A*（念做：A Star）算法是一种很常用的路径查找和图形遍历算法。它有较好的性能和准确度

https://zhuanlan.zhihu.com/p/54510444

## 启发式搜索题目

[宫水三叶的题库](https://github.com/SharingSource/LogicStack-LeetCode/wiki/%E5%90%AF%E5%8F%91%E5%BC%8F%E6%90%9C%E7%B4%A2): 

![image-20211109155848235](D:\gitCode\leetcode-exercise\problems\搜索算法\记忆化搜索概述\image-20211109155848235.png)



## 迭代加深搜索

首先深度优先搜索k层，若没有找到可行解，再深度优先搜索k+1层，直到找到可行解为止。

**优点**

1. 时间复杂度只比BFS稍差一点（虽然搜索k+1层时会重复搜索k层，但是整体而言并不比广搜慢很多）。

2. 空间复杂度与深搜相同，却比广搜小很多

3. 利于剪枝

> **例题 ：**
>
> Description
> Avery Boy 最近迷上了旋转游戏。旋转游戏使用＃形板，可以容纳24块方块（见图）。这些块标有数字1,2和3，每种正好有8个。
>
> ![image-20211109161215620](D:\gitCode\leetcode-exercise\problems\搜索算法\记忆化搜索概述\image-20211109161215620.png)
>
> 最初块随放在板子上，你的目标是移动块，使放置在中心方块的八个块具有相同的符号标记。只有一种类型的有效移动，即旋转四条线中的一条，每条线由七个块组成。也就是说，线中的六个块向头部移动一个块，并且头块移动到线的末端。八个可能的移动用大写字母A到H标记。图示出了两个连续的移动，移动A和移动C。
>
> **Input**
> 输入包含不超过30个测试用例。每个测试用例只有一行包含24个数字，这些数字是初始配置中块的符号。块的行从上到下列出。对于每一行，块从左到右列出。数字用空格分隔。例如，样例输入中的第一个测试用例对应于图中的初始配置。案件之间没有空行。在结束输入的最后一个测试用例之后，有一行包含单个“0”。
>
> **Output**
> 对于每个测试用例，您必须输出两行。第一行包含达到最终配置所需的所有动作。每个动作都是一个字母，从“A”到“H”，并且行中的字母之间不应有任何空格。如果不需要移动，则输出“No moves needed”。在第二行中，您必须在这些移动后输出中心方块中的块数字。如果有多种可能的解决方案，则必须输出使用最少移动次数的解决方案。如果仍有多个可能的解决方案，则必须输出字典顺序中最小的解决方案。不需要在案例之间输出空行。
>
> **Sample Input**
> 1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3
> 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3
> 0
> **Sample Output**
> AC
> 2
> DDHH
> 2

```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag=false;
char finop[20];
int reverseop[9]={5,4,7,6,1,0,3,2,-1};
int mp[24];
int pos[8][7]= // # 盘的形状
{
  { 0,2,6,11,15,20,22 },    //A
  { 1,3,8,12,17,21,23 },    //B
  { 10,9,8,7,6,5,4 },       //C
  { 19,18,17,16,15,14,13 }, //D
  { 23,21,17,12,8,3,1 },    //E
  { 22,20,15,11,6,2,0 },    //F
  { 13,14,15,16,17,18,19}, //G
  { 4,5,6,7,8,9,10 }      //H
};
int center[8]={6,7,8,11,12,15,16,17};
 
void option(int op) // 操作
{
    int temp=mp[pos[op][0]];
    for (int i=0;i<6;i++)
    {
      mp[pos[op][i]]=mp[pos[op][i + 1]];
    }
    mp[pos[op][6]]=temp;
}
bool cmp(int a,int b) // 比较大小
{
    return a>b;
}
 
int get_h(){ // 获取中间8个格子中的众数情况
    int cnt[3]={0,0,0};
    for (int i = 0; i < 8; i++){
        cnt[mp[center[i]] - 1]++;
    }
    sort(cnt,cnt+3,cmp);
    return 8-cnt[0];
}
 
void dfs(int depth,int lastop,int maxdepth)
{
    if(flag) // 如果找到了就返回了
      return;
    if(depth>maxdepth||depth+get_h()>maxdepth) //剪枝
      return;
    if(get_h()==0) // 正好找到
    {
      flag=true;
      //输出结果
          finop[depth]='\0';
          cout<<finop<<endl;
          cout<<mp[center[0]]<<endl;
      return;
    }
    for(int nextop=0;nextop<8;nextop++)
    {
        if(nextop!=reverseop[lastop])
        {
            //这个游戏一定有找到答案的那一天
            option(nextop);
            finop[depth]=nextop+'A';
            
            dfs(depth+1,nextop,maxdepth);
            option(reverseop[nextop]);
        }
    }
}
 
int main()
{
    while(1)
    {
        for(int i=0;i<24;i++)
        {//建立map
            cin>>mp[i];
            if(i==0)
            {
               if(mp[i]==0)
               return 0;
            }
         }
         if(!get_h())
         {//不需要移动
             cout<<"No moves needed"<<endl;
             cout<<mp[center[0]]<<endl;
             continue;
         }
         else
         {
             flag=false;
             for(int maxdepth=1;!flag;maxdepth++)
                dfs(0,8,maxdepth);
         }
    }
    return 0;
}
```



## 记忆化搜索概述

搜索的低效在于没有能够很好地处理重叠子问题；  
动态规划虽然比较好地处理了重叠子问题，但是在有些拓扑关系比较复杂的题目面前，又显得无奈。  
记忆化搜索正是在这样的情况下产生的，它采用搜索的形式和动态规划中递推的思想将这两种方法有机地综合在一起，扬长避短，简单实用，在信息学中有着重要的作用。

记忆化搜索的实现:

1. 首先，要通过一个表记录已经存储下的搜索结果，一般用哈希表实现

2. 状态表示，由于是要用哈希表实现，所以状态最好可以用数字表示，常用的方法是把一个状态连写成一个 p 进制数字，然后把这个数字对应的十进制数字作为状态

3. 在每一状态搜索的开始，高效的使用哈希表搜索这个状态是否出现过，如果已经做过，直接调用答案，回溯

4. 如果没有，则按正常方法搜索
