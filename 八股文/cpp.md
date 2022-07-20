# 标识符

## extern & static

static有两种使用：一种是修饰变量，另一种是修饰函数

extern的作用就是声明变量或者声明函数，然后能在使用extern的文件中使用这个全局变量或者函数（由别的变量定义）。

https://blog.csdn.net/qq_64426102/article/details/124084635

## extern “C”

[extern "C"：实现C++和C的混合编程 (biancheng.net)](http://c.biancheng.net/view/8064.html)

# 内存&存储方式

### 大端存储和小端储存？

**大端模式** ： 数据的高字节保存在[内存](https://so.csdn.net/so/search?q=%E5%86%85%E5%AD%98&spm=1001.2101.3001.7020)的低地址中。

**小端模式** ：高字节保存在内存的高地址中。

存储 0x12345678 如下：

低地址 --------------------> 高地址

`大端`
0x12 | 0x34 | 0x56 | 0x78
`小端`
0x78 | 0x56 | 0x34 | 0x12

```cpp
#include <iostream>
using namespace std;
 
void IsBigEndian()
{
        int a = 0x1234;
        char b =  *(char *)&a;  //通过将int强制类型转换成char单字节，通过判断起始存储位置。即等于 取b等于a的低地址部分
        if( b == 0x12)
        {
           cout<<"big endian"<<endl;
           return;
        }
        cout<<"small endian"<<endl;
        return;
}
 
int main()
{
 IsBigEndian();
}
```



### new, delete 和 malloc, free 的区别

相同点：

- 都是从堆上申请空间，并且需要用户手动释放。

不同点：

- malloc和free是标准库函数，支持覆盖；new和delete是运算符，并且支持重载。

- malloc申请的空间不会初始化，new可以初始化。malloc仅仅分配内存空间，不具备调用构造函数功能；new除了分配空间外，还会调用构造函数。

- malloc分配内存失败时返回NULL；new内存分配失败时，会抛出bac_alloc异常。

- malloc返回的是void类型指针（必须进行类型转换），new返回的是具体类型指针。

- malloc需要显式地指出所需内存的尺寸，使用new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算。

- malloc/free只会开辟空间，不会调用构造函数与析构函数，而new在申请空间后会调用构造函数完成对象的初始化，delete会释放空间前会调用析构函数完成空间中资源的清理。

### C/C++（内存对齐问题）&& struct 和 union的区别

struct 和class 内存对齐的三条原则：

- 每个数据成员存储的启始位置要从该成员大小，或者该成员子成员大小的整数倍开始。
- 子成员为struct 或者 class 时，该子成员要从其内部最大元素大小的整数倍地址开始存储
- 结构体在计算总大小时，必须是其内部最大成员长度（即前面内存对齐指令中提到的有效值）的整数倍，不足要补齐。

注意点

- 数组在内存中存储时是分开的，对齐按照单个元素对齐
- union 类型中的数据公用内存，联合的所有成员共用一段内存空间，存储地址的启示位置都相同，一般来说最大成员的内存宽度作为union的内存大小，主要的原因是为了节省内存空间，默认方位权限是公有的，但是它同样要遵循内存对齐的原则。
- C++中空结构体/空类占用 1 Byte

https://blog.csdn.net/luolaihua2018/article/details/115372273



# 多态和虚函数

## 虚函数与重载

- 面向对象语言的三大特性是：继承、封装、多态。虚函数作为多态的实现方式，重要性毋庸置疑。多态意指相同的消息给予不同的对象会引发不同的动作
- 重载——编译时多态的体现，一个类中同名不同参数的函数调用，这样的方法调用是在编译时确定的。
- 虚函数——运行时多态的体现，继承关系、虚函数覆盖、父类指针指向子类。

## 实例

```cpp

class base{
    public:
    	virtual void vir_func(){
            cout<<"virtual function, this is class base"<<endl;
        }
    	void func(){
            cout<<"normal function, this is class base"<<endl;
        }
}

class A: public base{
    public:
    	virtual void vir_func(){
            cout<<"virtual function, this is class A"<<endl;
        }
    	void func(){
            cout<<"normal function, this is class A"<<endl;
        }
}

class B{
    public:
    	virtual void vir_func(){
            cout<<"virtual function, this is class B"<<endl;
        }
    	void func(){
            cout<<"normal function, this is class B"<<endl;
        }
}


int main(){
    base * Base = new(base);
    base * a = new(A);
    base * b = new(B);
    Base->func(); a->func(); b->func();
    cout<<"*****"<<endl;
    Base->vir_func(); a->vir_func(); b->vir_func();
	cout<<"*****"<<endl;
    ((A*)b)->vir_func();
    ((A*)b)->func();
}


/* 输出
normal function, this is class base
normal function, this is class base
normal function, this is class base
*****
virtual function, this is class base
virtual function, this is class A
virtual function, this is class B
*****
virtual function, this is class B
normal function, this is class A
*/
```

当使用类的指针调用成员函数时，普通函数由指针类型决定，而虚函数由指针指向的实际类型决定。

虚函数通过内存中的 `vptr` 找到虚函数表 `vtbl`，接着通过 `vtbl` 找到对应虚函数的实现区域并进行调用。

## 虚函数的内存布局

只要有虚函数，C++类都会存在这样的一张虚函数表，不管是普通虚函数或者是纯虚函数，或者是派生类中的隐式声明的这些虚函数都会生成这张虚函数表。

虚函数表是在类构造的时候创建的，而这个虚函数表是提供整个类所共有的。虚函数表存储在对象最开始的位置。

虚函数表启示是函数指针的地址，函数调用的时候，通过函数指针所指向的函数来调用函数。

