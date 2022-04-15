# 0 说明

本文档记录一些 C++ 刷题时常用的函数和技巧

# 1 Data structure

## 1.1 vector (vector in cpp)

### 1.1.1 vector 排序

```cpp
//default
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);
//custom
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

- 参数:

  - **first, last:** 两个迭代器，用来指定范围
  - **comp:** 仿函数 用来自定义排序方法
- 返回值：None
- 例子：http://www.cplusplus.com/reference/algorithm/sort/
- cpp 自带模板仿函数 greater 和 less

```cpp
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
sort(RandomAccessIterator first, RandomAccessIterator last, greater<T>) //由小到大排序
template <class T> struct less {
  bool operator() (const T& x, const T& y) const {return x<y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
sort(RandomAccessIterator first, RandomAccessIterator last, less<T>) //由大到小排序
```

#### 自定义排序

```cpp
# 普通函数
bool myfunction (int i,int j) { return (i<j); }
# 仿函数 仿函数相关测试代码在 test-code/functor.cpp

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;

class F1{
public:
    virtual bool operator()(int i, int j) { return (i<j);}
};

#匿名函数
auto func = [/*外部变量*/](int A, int B){return A>B;};
```

### 1.1.2 vector 最值

```cpp
#include <algorithm>
#include <vector>

int main(){
vector<int> nums = {1,2,4,3};
int maxValue = *max_element(nums.begin(),nums.end()); // 4
int minValue = *min_element(nums.begin(),nums.end()); // 1
return 0;
}
```

- 参数:

  - **first, last:** 两个迭代器，用来指定范围
  - **comp:** 仿函数 用来自定义排序方法
- 返回值：最值元素
- 例子：

  - http://www.cplusplus.com/reference/algorithm/min_element/
  - http://www.cplusplus.com/reference/algorithm/max_element/

### 1.1.3 vector 截取

[C++容器vector的数组片段截取操作_stitching的博客-CSDN博客_c++ vector 截取](https://blog.csdn.net/qq_40250056/article/details/114681940)

## 1.2 stack (STL stack)

### 1.2.1 stack 声明

```cpp
template <class T, class Container = deque<T> > class stack;
```

> **stacks** are implemented as _container adaptors_, which are classes that use an encapsulated object of a specific container class as its _underlying container_, providing a specific set of member functions to access its elements. Elements are _pushed_/_popped_ from the _"back"_ of the specific container, which is known as the _top_ of the stack.
>
> The underlying container may be any of the standard container class templates or some other specifically designed container class. The container shall support the following operations:
>
> - empty
> - size
> - back
> - push_back
> - pop_back
>
> The standard container classes [vector](http://www.cplusplus.com/vector), [deque](http://www.cplusplus.com/deque) and [list](http://www.cplusplus.com/list) fulfill these requirements. By default, if no container class is specified for a particular stack class instantiation, the standard container [deque](http://www.cplusplus.com/deque) is used.

### 1.2.2 stack 函数

- [**(constructor)**](http://www.cplusplus.com/reference/stack/stack/stack/) Construct stack (public member function )
- [**empty**](http://www.cplusplus.com/reference/stack/stack/empty/) Test whether container is empty (public member function )
- [**size**](http://www.cplusplus.com/reference/stack/stack/size/) Return size (public member function )
- [**top**](http://www.cplusplus.com/reference/stack/stack/top/) Access next element (public member function )
- [**push**](http://www.cplusplus.com/reference/stack/stack/push/) Insert element (public member function )
- [**emplace** ](http://www.cplusplus.com/reference/stack/stack/emplace/) Construct and insert element (public member function )
- [**pop**](http://www.cplusplus.com/reference/stack/stack/pop/) Remove top element (public member function )
- [**swap** ](http://www.cplusplus.com/reference/stack/stack/swap/) Swap contents (public member function )

## 1.3 std::[string](http://www.cplusplus.com/reference/string/string/)

### 1.3.1 string::substr

```cpp
constexpr basic_string_view
    substr(size_type __pos, size_type __n = npos) const noexcept(false)
{
    __pos = _M_check(__pos, "basic_string_view::substr");
    const size_type __rlen = std::min(__n, _M_len - __pos);
    return basic_string_view{_M_str + __pos, __rlen};
}
```

**Parameters**

- `pos`

  Position of the first character to be copied as a substring. If this is equal to the *[string length](http://www.cplusplus.com/string::length)*, the function returns an empty string. If this is greater than the *[string length](http://www.cplusplus.com/string::length)*, it throws [out_of_range](http://www.cplusplus.com/out_of_range). Note: The first character is denoted by a value of `0` (not `1`).
- `len`

  Number of characters to include in the substring (==if the string is shorter, as many characters as possible are used==). A value of [string::npos](http://www.cplusplus.com/string::npos) indicates all characters until the end of the string.
- [`size_t`](http://www.cplusplus.com/size_t) is an unsigned integral type (the same as member type [string::size_type](http://www.cplusplus.com/string#types)).

**Return Value**

A [string](http://www.cplusplus.com/string) object with a substring of this object.

**Example**

```cpp
// string::substr
#include <iostream>
#include <string>

int main ()
{
  std::string str="We think in generalities, but we live in details.";
                                           // (quoting Alfred N. Whitehead)

  std::strin-g str2 = str.substr (3,5);     // "think"

  std::size_t pos = str.find("live");      // position of "live" in str

  std::string str3 = str.substr (pos);     // get from "live" to the end

  std::cout << str2 << ' ' << str3 << '\n';

  return 0;
}
```

## 1.4 std::priority_queue

### 1.4.1 Abstract

Priority queues are a type of container adaptors, specifically designed such that **its first element is always the ==greatest== of (by default) the elements it contains**, according to some *strict weak ordering* criterion.

Priority queues are implemented as *container adaptors*, which are classes that use an encapsulated object of a specific container class as its *underlying container*, providing a specific set of member functions to access its elements. **Elements are *popped* from the *=="back"==* of the specific container**, which is known as **the ==*top*== of the priority queue**.

The standard container classes [vector](http://www.cplusplus.com/vector) and [deque](http://www.cplusplus.com/deque) fulfill these the basic function requirements of priority queues. By default, if no container class is specified for a particular [priority_queue](http://www.cplusplus.com/priority_queue) class instantiation, the standard container [vector](http://www.cplusplus.com/vector) is used.

### 1.4.2 Template parameters

**T**

> Type of the elements. Aliased as member type priority_queue::value_type.

**Container**

>     Type of the internal*underlying container* object where the elements are stored.
> Its value_type shall be T. Aliased as member type priority_queue::container_type.

**Compare**

>     A binary predicate that takes two elements (of type T) as arguments and returns a`bool`.
> 	The expression `comp(a,b)`, where comp is an object of this type and a and b are elements in the container,  **shall return `true` if a is considered to go before b in the *strict weak ordering* the function defines.**
> 	The priority_queue uses this function to maintain the elements sorted in a way that preserves *heap properties* (i.e., that the element popped is the last according to this *strict weak ordering*).
> 	This can be a function pointer or a function object, and **defaults to `less<T>`**, which returns the same as applying the *less-than operator* (`a<b`).

- [**(constructor)**](http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/) Construct priority queue (public member function )
- [**empty**](http://www.cplusplus.com/reference/queue/priority_queue/empty/) Test whether container is empty (public member function )
- [**size**](http://www.cplusplus.com/reference/queue/priority_queue/size/) Return size (public member function )
- [**top**](http://www.cplusplus.com/reference/queue/priority_queue/top/) Access top element (public member function )
- [**push**](http://www.cplusplus.com/reference/queue/priority_queue/push/) Insert element (public member function )
- [**emplace** ](http://www.cplusplus.com/reference/queue/priority_queue/emplace/) Construct and insert element (public member function )
- [**pop**](http://www.cplusplus.com/reference/queue/priority_queue/pop/) Remove top element (public member function )
- [**swap** ](http://www.cplusplus.com/reference/queue/priority_queue/swap/) Swap contents (public member function )

```cpp
class student{
    public:
        int age;
        string name;
        /**重载小于操作符，
	      *这里必须是非成员函数才可以
		*/
        friend bool operator<(const student& a, const student & b){
            return a.age < b.age;
        }
};

/**可调用的函数操作符的对象*/
struct mycmp{
    bool operator()(const student & a,const student & b){
        return a.age < b.age;
    }
};

/**函数指针*/
bool cmpfunc(const student& a, const student& b){
    return a.age < b.age;
}

/**默认使用student的oprator<来进行比较*/
priority_queue<student> que1;

/**使用重载函数操作符的类对象*/
priority_queue<student,vector<student>,mycmp> que2;

/**定义一下比较函数*/
auto cmp = [](const student & a,const student & b){return a.age < b.age;};
/**
  *	需要把lambda表达式作为优先队列参数进行初始化
  * 并且指定priority_queue的模板实参，decltype(cmp)，c++11 declare type，声明类型
  * 可以认为是确定函数的类型
  * bool (const student & a,const student & b)
**/
priority_queue<student,vector<student>,decltype(cmp)> que4(cmp);

/*使用函数对象来定义这个比较函数原型*/
//lambda 函数来初始化函数对象
priority_queue<student,vector<student>,function<bool(const student&,const student&)>> que5(cmp);

//函数指针来初始化函数对象
priority_queue<student,vector<student>,function<bool(const student&,const student&)>> que6(cmpfunc);

/**函数对象*/
function<bool(const student&,const student &)> func(cmpfunc);
priority_queue<student,vector<student>,function<bool(const student&,const student&)>> que7(func);
```

## 1.5 std::unordered_map

### 1.5.1 unordered_map的遍历

```cpp
unordered_map<int,int> mp;

// 迭代器遍历
unordered_map<int,int>::iterator it;
it = mp.begin();
while(it!=mp.end()){
    //do something
    it++;
}
// for遍历
for(auto [key,val] : mp){
    //do something
}

```

# 2 Functions

## 2.1 rand()

C++中rand() 函数的用法

1. rand()不需要参数，它会返回一个从0到最大随机数的任意整数，最大随机数的大小通常是固定的一个大整数。
2. 如果你要产生 `0~99` 这100个整数中的一个随机整数，可以表达为：`int num = rand() % 100; ` 这样，num的值就是一个0~99中的一个随机数了。

3、如果要产生1~100，则是这样：`int num = rand() % 100 + 1;`

4、总结来说，可以表示为：

```cpp
int num = rand() % n +a;
// 其中的a是起始值，n-1+a是终止值，n是整数的范围。
```

5、一般性：`rand() % (b-a+1)+ a ;`    就表示  a~b 之间的一个随机整数。

6、若要产生0\~1之间的小数，则可以先取得0\~10的整数，然后均除以10即可得到“随机到十分位”的10个随机小数。若要得到“随机到百分位”的随机小数，则需要先得到0\~100的10个整数，然后均除以100，其它情况依 此类推。

7、通常rand()产生的随机数在每次运行的时候都是与上一次相同的，这样是为了便于程序的调试。若要产生每次不同的随机数，则可以使用srand( seed )函数进行产生随机化种子，随着seed的不同，就能够产生不同的随机数。

8、还可以包含time.h头文件，然后使用srand(time(0))来使用当前时间使随机数发生器随机化，这样就可以保证每两次运行时可以得到不同的随机数序列，同时这要求程序的两次运行的间隔超过1秒。

## 2.2 atoi()  | to_string()

### 2.2.1 string 转 int

```cpp
#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
	char* s = "1234";
	string str("5678");
 
	int intS = atoi(s);
 
	//此写法会报错
	//int intStr = atoi(str);
	//需先将string转成char*
	int intStr = atoi(str.c_str());
 
	cout << "char* 转int:    " << intS << endl;
	cout << "string 转int:    " << intStr << endl;
 
	system("pause");
	return 0;
}
```

### 2.2.2 int 转 string

```cpp
to_sting();
```

## 2.3 upper_bound()

| default (1) | `template <class ForwardIterator, class T>  ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,                               const T& val); ` |
| ----------: | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|  custom (2) | `template <class ForwardIterator, class T, class Compare>  ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,const T& val, Compare comp);`    |

返回大于目标值的最小值的迭代器。

```cpp
// lower_bound/upper_bound example
#include <iostream>     // std::cout
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort
#include <vector>       // std::vector

int main () {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low,up;
  low=std::lower_bound (v.begin(), v.end(), 20); //          ^
  up= std::upper_bound (v.begin(), v.end(), 20); //                   ^

  std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
  std::cout << "upper_bound at position " << (up - v.begin()) << '\n';

  return 0;
}
```

## 2.3 swap()

```cpp
// swap algorithm example (C++11)
#include <iostream>     // std::cout
#include <utility>      // std::swap
#include <string>       // std::string

int main () {

  int x=10, y=20;                  // x:10 y:20
  std::swap(x,y);                  // x:20 y:10

  std::string s = "012345";
  std::swap(s[0],s[5]);
  for(char c : s) std::cout << ' ' << c;
  std::cout << std::endl;
  
  int foo[4];                    
  int bar[] = {10,20,30,40};     
  std::swap(foo,bar);
  for (int i: foo) std::cout << ' ' << i;
  std::cout << std::endl;


  return 0;
}
```

# 3 Grammar

## 3.1 lambda函数

    https://www.cnblogs.com/pzhfei/archive/2013/01/14/lambda_expression.html

## 3.2 类型转换

    https://www.cnblogs.com/sylar5/p/6638641.html
