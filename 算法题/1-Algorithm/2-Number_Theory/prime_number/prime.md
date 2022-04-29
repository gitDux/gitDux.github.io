## [204. 计数质数](https://leetcode-cn.com/problems/count-primes/)

给定整数 `n` ，返回 *所有小于非负整数 `n` 的质数的数量* 。

```cpp
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> judge(n,true);
	vector<int> resVec;
        int res = 0;
        for(int i = 2; i < n; i++){
            if(judge[i]){
                for(int j = 2*i; j < n; j+=i)
                    judge[j] = false;
                res += 1;
		resVec.push_back(i);
            }
        }
        return res;
    }
};
```



## [1175. 质数排列](https://leetcode-cn.com/problems/prime-arrangements/)

**难度**简单44收藏分享切换为英文接收动态反馈

请你帮忙给从 `1` 到 `n` 的数设计排列方案，使得所有的「质数」都应该被放在「质数索引」（索引从 1 开始）上；你需要返回可能的方案总数。

让我们一起来回顾一下「质数」：质数一定是大于 1 的，并且不能用两个小于它的正整数的乘积来表示。

由于答案可能会很大，所以请你返回答案 **模 mod `10^9 + 7`** 之后的结果即可。

```cpp
class Solution {
public:
    int MOD = 1000000000+7;
    int countPrimes(int n){
        vector<bool> judge(n+1,true);
        int res=0;
        for(int i=2; i <= n; i++){
            if(judge[i]){
                res++;
                for(int  j = i; j <= n; j+=i)
                    judge[j] = false;
            }
        }
        return res;
    }
    long factorial(int n){
        long res = 1;
        for(int i = 1; i <= n; i++){
            res *= i;
            res %=MOD;
        }
        return res;
    }
    int numPrimeArrangements(int n) {
        int numOfPrimes = countPrimes(n);

        return (factorial(numOfPrimes)*factorial(n-numOfPrimes))%MOD;
    }
};
```
