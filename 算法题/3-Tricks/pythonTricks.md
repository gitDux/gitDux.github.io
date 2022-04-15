# 0 说明
本文档记录一些 Python 刷题时常用的函数和技巧

https://www.cnblogs.com/zhangxinqi/p/9729406.html#_label8

# 1 Data structure

## 1.1 list (vector in cpp)

### 1.1.1 list 排序

```python
list.sort(cmp=None, key=None, reverse=False)
```

- 参数:
  - cmp  可选参数, 如果指定了该参数会使用该参数的方法进行排序。
  - key  主要是用来进行比较的元素，只有一个参数，具体的函数的参数就是取自于可迭代对象中，指定可迭代对象中的一个元素来进行排序。
  - reverse  排序规则，reverse = True 降序， reverse = False 升序（默认）。
- 返回值：None
- 例子：https://www.runoob.com/python/att-list-sort.html

### 1.1.2 list 最值

```python
max(list)
min(list)
```

- 参数:
  - list 要返回最值的列表
- 返回值：最值
- 例子：
    - https://docs.python.org/zh-cn/3.7/library/stdtypes.html#sequence-types-list-tuple-range
    - https://www.runoob.com/python/att-list-max.html
    - https://www.runoob.com/python/att-list-min.html

## 1.2 Dictionary (map in cpp)

### 1.2.1 Dictionary 
字典是另一种可变容器模型，且可存储任意类型对象。

字典的每个键值 key=>value 对用冒号 : 分割，每个键值对之间用逗号 , 分割，整个字典包括在花括号 {} 中 ,格式如下所示：
```python
d = {key1 : value1, key2 : value2 }
```
- 详细介绍：
    - https://www.runoob.com/python/python-dictionary.html

### 1.2.2 defaultdict

defaultdict  相比 dict 多了一个返回默认值的功能。

```python
#————————————————————defaultdict———————————————————
>>> from collections import defaultdict
>>> dic = defaultdict(int)
>>> dic[22]	#不存在的key 返回 int 的deault value
0
>>> dic[22] = 22

>>> dic[22]      
22
#———————————————————————dict———————————————————————
>>> dic = dict()
>>> dic[0]
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
KeyError: 0
```

- 详细介绍
  - https://www.jianshu.com/p/bbd258f99fd3

## 1.3 Stack (stack in cpp)

### 1.3.1 list to stack

python的内置数据结构list可以用来实现栈，用append()向栈顶添加元素, pop() 可以以后进先出的顺序删除元素。但是列表本身有一些缺点，主要问题就是当列表不断扩大的时候会遇到速度瓶颈．列表是动态数组，因此往其中添加新元素而没有空间保存新的元素时，它会自动重新分配内存块，并将原来的内存中的值复制到新的内存块中．这就导致了一些append()操作会消耗更多的时间。（这一点和cpp std vector 有点像）

```python
>>> stack = []
>>> #append() fuction to push
>>> stack.append('hello')
>>> stack.append('world')
>>> stack.append('!')
>>> print(stack)
['hello', 'world', '!']
>>> #pop() function to pop element
>>> print(stack.pop())
!
>>> print(stack.pop())
world
>>> print(stack.pop())
hello
Stack after all elements are poped
>>> print(len(stack))
0

```

### 1.3.2 collections.deque to stack

python中栈也可以用deque类实现，当我们想要在实现在容器两端更快速地进行append和pop操作时，deque比列表更合适．deque可以提供O(1)时间的append和pop操作，而列表则需要O(n)时间.

```python
>>> from collections import deque
>>> stack = deque()
>>> # append() fuction to push
>>> stack.append('hello')
>>> stack.append('world')
>>> stack.append('!')
>>> print(stack)
deque(['hello', 'world', '!'])
>>> #pop() function to pop element
>>> print(stack.pop())
!
>>> print(stack.pop())
world
>>> print(stack.pop())
hello
>>> print(len(stack))
0
```

### 1.3.3 queue.LifoQueue to stack

Queue模块有LIFO queue，也就是栈结构．用put()和get()操作从Queue中添加和获得数据

```python
>>> from queue import LifoQueue
>>> stack = LifoQueue(maxsize = 3)
>>> print(stack.qsize())
0
>>> stack.put('hello')
>>> stack.put('world')
>>> stack.put('!')
>>> print('\nElement poped from stack')
>>> print(stack.get())
!
>>> print(stack.get())
world
>>> print(stack.get())
hello
>>> print('\nEmpty:', stack.empty())
Empty: True
```

### 1.3.4 参考链接

​	https://www.jb51.net/article/202477.htm



# 2 Functions

## `List sort()`

sort() 函数用于对原列表进行排序，如果指定参数，则使用比较函数指定的比较函数。

```python
list.sort( key=None, reverse=False)
```

**参数**

- key -- 主要是用来进行比较的元素，只有一个参数，具体的函数的参数就是取自于可迭代对象中，指定可迭代对象中的一个元素来进行排序。
- reverse -- 排序规则，**reverse = True** 降序， **reverse = False** 升序（默认）。

**返回值**

- 该方法没有返回值，但是会对列表的对象进行排序。

**参考**

https://www.runoob.com/python3/python3-att-list-sort.html

https://docs.python.org/zh-cn/3.6/howto/sorting.html

## `range()`

```python
range(start, stop[, step])
```

- 参数
  - start  计数从 start 开始。默认是从 0 开始。例如range（5）等价于range（0， 5）;
  - stop  计数到 stop 结束，但不包括 stop。例如：range（0， 5） 是[0, 1, 2, 3, 4]没有5
  - step  步长，默认为1。例如：range（0， 5） 等价于 range(0, 5, 1)

```python
>>>range(5)
range(0, 5)
>>> list(range(5))
[0, 1, 2, 3, 4]
>>> list(range(0))
[]
>>>list(range(0, 30, 5))
[0, 5, 10, 15, 20, 25]
>>> list(range(0, 10, 2)) # 间隔遍历
[0, 2, 4, 6, 8]
>>> list(range(0, -10, -1)) # 逆序遍历
[0, -1, -2, -3, -4, -5, -6, -7, -8, -9]
>>> list(range(1, 0))
[]
```

## `enumerate()`

```python
enumerate(sequence, [start=0])
```

**参数**

- sequence -- 一个序列、迭代器或其他支持迭代对象。
- start -- 下标起始位置。

**示例**

```python
>>>seasons = ['Spring', 'Summer', 'Fall', 'Winter']
>>> list(enumerate(seasons))
[(0, 'Spring'), (1, 'Summer'), (2, 'Fall'), (3, 'Winter')]
>>> list(enumerate(seasons, start=1))       # 下标从 1 开始
[(1, 'Spring'), (2, 'Summer'), (3, 'Fall'), (4, 'Winter')]
```

**使用在for循环中：**

```python
>>>seq = ['one', 'two', 'three']
>>> for i, element in enumerate(seq):
...     print i, element
... 
0 one
1 two
2 three
```

## `random()`

```python
#!/usr/bin/python
# -*- coding: UTF-8 -*-

import random
import string

# 随机整数：
print random.randint(1,50) # 闭区间[]

# 随机选取0到100间的偶数：
print random.randrange(0, 101, 2)#[ 由于选择步长是2 所以到不了101

# 随机浮点数：
print random.random() # 0-1 浮点数
print random.uniform(1, 10) # 均匀分布浮点数

# 随机字符：
print random.choice('abcdefghijklmnopqrstuvwxyz!@#$%^&*()')

# 多个字符中生成指定数量的随机字符：
print random.sample('zyxwvutsrqponmlkjihgfedcba',5)

# 从a-zA-Z0-9生成指定数量的随机字符：
ran_str = ''.join(random.sample(string.ascii_letters + string.digits, 8))
print ran_str

# 多个字符中选取指定数量的字符组成新字符串：
print ''.join(random.sample(['z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'], 5))

# 随机选取字符串：
print random.choice(['剪刀', '石头', '布'])

# 打乱排序
items = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
print random.shuffle(items)
```

## `zip()`

python3 **zip()** 函数用于将可迭代的对象作为参数，将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的对象，这样做的好处是节约了不少的内存。

我们可以使用 list() 转换来输出列表。

如果各个迭代器的元素个数不一致，则返回列表长度与最短的对象相同，利用 ***** 号操作符，可以将元组解压为列表。

**zip 语法：**

```python
zip([iterable, ...])
```

**参数说明：**

- iterabl -- 一个或多个迭代器;

**返回值**

一个对象

**示例**

```python
>>>a = [1,2,3]
>>> b = [4,5,6]
>>> c = [4,5,6,7,8]
>>> zipped = zip(a,b)       # 返回一个对象
>>> zipped
<zip object at 0x103abc288>
>>> list(zipped)            # list() 转换为列表
[(1, 4), (2, 5), (3, 6)]
>>> list(zip(a,c))          # 元素个数与最短的列表一致
[(1, 4), (2, 5), (3, 6)]
>>> a1, a2 = zip(*zip(a,b)) # 与 zip 相反，zip(*) 可理解为解压，返回二维矩阵式
>>> list(a1)
[1, 2, 3]
>>> list(a2)
[4, 5, 6]
>>>
```

## `bisect()`

```python
from bisect imoprt *

bisect_left(list,target) // 与CPP的lower_bound一个意思
bisect_right(list,target)// 与CPP的upper_bound一个意思
```



# 3 Features

## 交换swap

```python
def swap(a,b):
    a,b = b,a
    print(a,b)
```

## Python数据类型转换

有时候，我们需要对数据内置的类型进行转换，数据类型的转换，你只需要将数据类型作为函数名即可。以下几个内置的函数可以执行数据类型之间的转换。这些函数返回一个新的对象，表示转换的值。

| 函数                                                         | 描述                                                |
| :----------------------------------------------------------- | :-------------------------------------------------- |
| [int(x [,base])](https://www.runoob.com/python3/python-func-int.html) | 将x转换为一个整数                                   |
| [float(x)](https://www.runoob.com/python3/python-func-float.html) | 将x转换到一个浮点数                                 |
| [complex(real [,imag])](https://www.runoob.com/python3/python-func-complex.html) | 创建一个复数                                        |
| [str(x)](https://www.runoob.com/python3/python-func-str.html) | 将对象 x 转换为字符串                               |
| [repr(x)](https://www.runoob.com/python3/python-func-repr.html) | 将对象 x 转换为表达式字符串                         |
| [eval(str)](https://www.runoob.com/python3/python-func-eval.html) | 用来计算在字符串中的有效Python表达式,并返回一个对象 |
| [tuple(s)](https://www.runoob.com/python3/python3-func-tuple.html) | 将序列 s 转换为一个元组                             |
| [list(s)](https://www.runoob.com/python3/python3-att-list-list.html) | 将序列 s 转换为一个列表                             |
| [set(s)](https://www.runoob.com/python3/python-func-set.html) | 转换为可变集合                                      |
| [dict(d)](https://www.runoob.com/python3/python-func-dict.html) | 创建一个字典。d 必须是一个 (key, value)元组序列。   |
| [frozenset(s)](https://www.runoob.com/python3/python-func-frozenset.html) | 转换为不可变集合                                    |
| [chr(x)](https://www.runoob.com/python3/python-func-chr.html) | 将一个整数转换为一个字符                            |
| [ord(x)](https://www.runoob.com/python3/python-func-ord.html) | 将一个字符转换为它的整数值                          |
| [hex(x)](https://www.runoob.com/python3/python-func-hex.html) | 将一个整数转换为一个十六进制字符串                  |
| [oct(x)](https://www.runoob.com/python3/python-func-oct.html) | 将一个整数转换为一个八进制字符串                    |

> set(s) 可以用来去重

```python
>>> l = "aajsdd"
>>> set(l)
{'s', 'a', 'd', 'j'}
>>> len(set(l))
4
>>> len(l)
6
```



## Python算术运算符

以下假设变量 `a=10`，变量 `b=21`：

| 运算符 | 描述                                            | 实例                      |
| :----- | :---------------------------------------------- | :------------------------ |
| +      | 加 - 两个对象相加                               | a + b 输出结果 31         |
| -      | 减 - 得到负数或是一个数减去另一个数             | a - b 输出结果 -11        |
| *      | 乘 - 两个数相乘或是返回一个被重复若干次的字符串 | a * b 输出结果 210        |
| /      | 除 - x 除以 y                                   | b / a 输出结果 2.1        |
| %      | 取模 - 返回除法的余数                           | b % a 输出结果 1          |
| **     | 幂 - 返回x的y次幂                               | a**b 为10的21次方         |
| //     | 取整除 - 向下取接近商的整数                     | `>>> 9//2 4 >>> -9//2 -5` |

## Python常用数学函数

| 函数                                                         | 返回值 ( 描述 )                                              |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| [abs(x)](https://www.runoob.com/python3/python3-func-number-abs.html) | 返回数字的绝对值，如abs(-10) 返回 10                         |
| [ceil(x)](https://www.runoob.com/python3/python3-func-number-ceil.html) | 返回数字的上入整数，如math.ceil(4.1) 返回 5                  |
| cmp(x, y)                                                    | 如果 x < y 返回 -1, 如果 x == y 返回 0, 如果 x > y 返回 1。 **Python 3 已废弃，使用 (x>y)-(x<y) 替换**。 |
| [exp(x)](https://www.runoob.com/python3/python3-func-number-exp.html) | 返回e的x次幂(ex),如math.exp(1) 返回2.718281828459045         |
| [fabs(x)](https://www.runoob.com/python3/python3-func-number-fabs.html) | 返回数字的绝对值，如math.fabs(-10) 返回10.0                  |
| [floor(x)](https://www.runoob.com/python3/python3-func-number-floor.html) | 返回数字的下舍整数，如math.floor(4.9)返回 4                  |
| [log(x)](https://www.runoob.com/python3/python3-func-number-log.html) | 如math.log(math.e)返回1.0,math.log(100,10)返回2.0            |
| [log10(x)](https://www.runoob.com/python3/python3-func-number-log10.html) | 返回以10为基数的x的对数，如math.log10(100)返回 2.0           |
| [max(x1, x2,...)](https://www.runoob.com/python3/python3-func-number-max.html) | 返回给定参数的最大值，参数可以为序列。                       |
| [min(x1, x2,...)](https://www.runoob.com/python3/python3-func-number-min.html) | 返回给定参数的最小值，参数可以为序列。                       |
| [modf(x)](https://www.runoob.com/python3/python3-func-number-modf.html) | 返回x的整数部分与小数部分，两部分的数值符号与x相同，整数部分以浮点型表示。 |
| [pow(x, y)](https://www.runoob.com/python3/python3-func-number-pow.html) | x**y 运算后的值。                                            |
| [round(x [,n])](https://www.runoob.com/python3/python3-func-number-round.html) | 返回浮点数 x 的四舍五入值，如给出 n 值，则代表舍入到小数点后的位数。**其实准确的说是保留值将保留到离上一位更近的一端。** |
| [sqrt(x)](https://www.runoob.com/python3/python3-func-number-sqrt.html) | 返回数字x的平方根。                                          |

## Python 随机数函数

随机数可以用于数学，游戏，安全等领域中，还经常被嵌入到算法中，用以提高算法效率，并提高程序的安全性。Python包含以下常用随机数函数：

| 函数                                                         | 描述                                                         |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| [choice(seq)](https://www.runoob.com/python3/python3-func-number-choice.html) | 从序列的元素中随机挑选一个元素，比如random.choice(range(10))，从0到9中随机挑选一个整数。 |
| [randrange ([start,\] stop [,step])](https://www.runoob.com/python3/python3-func-number-randrange.html) | 从指定范围内，按指定基数递增的集合中获取一个随机数，基数默认值为 1 |
| [random()](https://www.runoob.com/python3/python3-func-number-random.html) | 随机生成下一个实数，它在[0,1)范围内。                        |
| [seed([x])](https://www.runoob.com/python3/python3-func-number-seed.html) | 改变随机数生成器的种子seed。如果你不了解其原理，你不必特别去设定seed，Python会帮你选择seed。 |
| [shuffle(lst)](https://www.runoob.com/python3/python3-func-number-shuffle.html) | 将序列的所有元素随机排序                                     |
| [uniform(x, y)](https://www.runoob.com/python3/python3-func-number-uniform.html) | 随机生成下一个实数，它在[x,y]范围内。                        |

## Python 字符串运算

| 操作符 | 描述                                                         | 实例                            |
| :----- | :----------------------------------------------------------- | :------------------------------ |
| +      | 字符串连接                                                   | a + b 输出结果： HelloPython    |
| *      | 重复输出字符串                                               | a*2 输出结果：HelloHello        |
| []     | 通过索引获取字符串中字符                                     | a[1] 输出结果 **e**             |
| [ : ]  | 截取字符串中的一部分，遵循**左闭右开**原则，str[0:2] 是不包含第 3 个字符的。 | a[1:4] 输出结果 **ell**         |
| in     | 成员运算符 - 如果字符串中包含给定的字符返回 True             | **'H' in a** 输出结果 True      |
| not in | 成员运算符 - 如果字符串中不包含给定的字符返回 True           | **'M' not in a** 输出结果 True  |
| r/R    | 原始字符串 - 原始字符串：所有的字符串都是直接按照字面的意思来使用，没有转义特殊或不能打印的字符。 原始字符串除在字符串的第一个引号前加上字母 **r**（可以大小写）以外，与普通字符串有着几乎完全相同的语法。 | `print( r'\n' ) print( R'\n' )` |
| %      | 格式字符串                                                   | 请看下一节内容。                |

