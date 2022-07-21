# 标识符

## extern & static

static有两种使用：一种是修饰变量，另一种是修饰函数

extern的作用就是声明变量或者声明函数，然后能在使用extern的文件中使用这个全局变量或者函数（由别的变量定义）。

https://blog.csdn.net/qq_64426102/article/details/124084635

## extern “C”

[extern &#34;C&#34;：实现C++和C的混合编程 (biancheng.net)](http://c.biancheng.net/view/8064.html)

# 内存&存储方式

### 大端存储和小端储存？

**大端模式** ： 数据的高字节保存在[内存](https://so.csdn.net/so/search?q=%E5%86%85%E5%AD%98&spm=1001.2101.3001.7020)的低地址中。

**小端模式** ：高字节保存在内存的高地址中。

存储 0x12345678 如下：

高地址 --------------------> 低地址

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

### malloc的底层系统调用及原理

关键词：内存池、mmap\bark、free 16字节、虚拟内存和物理内存

https://blog.csdn.net/qq_36638788/article/details/124593704

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

# 继承、多态、封装

# 构造函数和析构函数可以调用虚函数吗

https://blog.csdn.net/weixin_41066529/article/details/89496385

https://blog.csdn.net/imJaron/article/details/79676619

### C++的空类有哪些成员函数

- 缺省构造函数。
- 缺省拷贝构造函数。
- 缺省析构函数。
- 缺省赋值运算符。
- 缺省取址运算符。
- 缺省取址运算符 const。

注意：有些书上只是简单的介绍了前四个函数。没有提及后面这两个函数。但后面这两个函数也是空类的默认函数。另外需要注意的是，只有当实际使用这些函数的时候，编译器才会去定义它们。

---

原文链接：https://blog.csdn.net/BostonRayAlen/article/details/93041395

### 虚函数与重载

- 面向对象语言的三大特性是：继承、封装、多态。虚函数作为多态的实现方式，重要性毋庸置疑。多态意指相同的消息给予不同的对象会引发不同的动作
- 重载——编译时多态的体现，一个类中同名不同参数的函数调用，这样的方法调用是在编译时确定的。
- 虚函数——运行时多态的体现，继承关系、虚函数覆盖、父类指针指向子类。

实例

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

### 虚函数的内存布局

只要有虚函数，C++类都会存在这样的一张虚函数表，不管是普通虚函数或者是纯虚函数，或者是派生类中的隐式声明的这些虚函数都会生成这张虚函数表。

虚函数表是在类构造的时候创建的，而这个虚函数表是提供整个类所共有的。虚函数表存储在对象最开始的位置。

虚函数表启示是函数指针的地址，函数调用的时候，通过函数指针所指向的函数来调用函数。

# 新特性

## C++ 11 新特性

### auto 和 decltype `类型推导`

auto: 对于变量，指定要从其初始化类型自动推导出其类型。

```cpp
auto a = 10;    // 自动推导 a 为 int
auto b = 10.2;  // 自动推导 b 为 double
auto c = &a;    // 自动推导 c 为 int*
auto d = "xxx"; // 自动推导 d 为 const char*
```

decltype: 推导实体的声明类型，或表达式的类型。为了解决 auto 关键字只能对变量进⾏类型推导的缺陷⽽出现。

```cpp
int a = 0;
 
decltype(a) b = 1;        // b 被推导为 int 类型
decltype(10.8) c = 5.5;   // c 被推导为 double 类型
decltype(c + 100) d;      // d 被推导为 double
 
struct { double x; } aa;
decltype(aa.x) y;         // y 被推导为 double 类型
decltype(aa) bb;          // 推断匿名结构体类型
```

C++11 中 auto 和 decltype 结合再借助「尾置返回类型」还可推导函数的返回类型。从 C++14 开始⽀持仅⽤ auto 并实现返回类型推导，见下⽂ C++14 章节。

```cpp
// 利⽤ auto 关键字将返回类型后置
template<typename T, typename U>
auto add1(T x, U y) -> decltype(x + y) {
  return x + y;
}
```

### defaulted 与 deleted 函数

在 C++ 中，如果程序员没有⾃定义，那么编译器会**默认**为程序员⽣成 「**构造函数**」、「**拷贝构造函数**」、「**拷贝赋值函数**」 等。[见上文](#C++的空类有哪些成员函数)

但如果程序员⾃定义了上述函数，编译器则不会⾃动⽣成这些函数。

⽽在实际开发过程中，我们有时需要**在保留⼀些默认函数的同时禁⽌⼀些默认函数**。

例如创建 「**不允许拷贝的类**」 时，在传统 C++ 中，我们经常有如下的惯例代码：

```cpp
// 除非特别熟悉编译器自动生成特殊成员函数的所有规则，否则意图是不明确的
class noncopyable   {
public:
  // 由于下⽅有⾃定义的构造函数（拷⻉构造函数）
  // 编译器不再⽣成默认构造函数，所以这⾥需要⼿动定义构造函数
  // 但这种⼿动声明的构造函数没有编译器⾃动⽣成的默认构造函数执⾏效率⾼
  noncopyable() {};
private: 
  // 将拷⻉构造函数和拷⻉赋值函数设置为 private
  // 但却⽆法阻⽌友元函数以及类成员函数的调⽤
  noncopyable(const noncopyable&);
  noncopyable& operator=(const noncopyable&);
};
```

### final 与 override

C++11 引⼊

**override** 显式的声明**要覆盖基类的虚函数**，如果不存在这样的虚函数，将不会通过编译。

**final** 则终⽌虚类被继承或虚函数被覆盖

### 尾置返回类型

C++11 引⼊「尾置返回类型」，将「函数返回类型」通过 **-> 符号**连接到函数后面。尾置返回类型经常在 「**lambda 表达式**」、「**模板函数返回**」中使⽤

```cpp
// 使⽤尾置返回类型来声明 lambda 表达式的返回类型
[capture list] (params list) mutable exception->return_type { function body }
// 在模板函数返回中结合 auto\decltype 声明模板函数返回值类型
template<typename T, typename U>
auto add(T x, U y) -> decltype(x + y) {
  return x + y;
}
```

### 右值引用

**左值**：内存中有确定存储地址的对象的表达式的值

**右值**：所有不是左值的表达式的值。右值可分为「**传统纯右值**」和「**将亡值**」

**纯右值**：即 C++11 之前的右值。包括：

1. 常见的字面量如 0、"123"、或表达式为字面量
2. 不具名的临时对象，如函数返回临时对象

**将亡值**：随着 C++11 引入的右值引用而来的概念。包括：

1. 「返回右值引用的函数」的返回值。如返回类型为 T&& 的函数的返回值
2. 「转换为右值引用的转换函数」的返回值，如 std::move() 函数的返回值

C++11 之前，我们就经常使⽤对左值的引⽤，即左值引⽤，使用 & 符号声明

```cpp
int j = 0;
int& ref_j = j;           // ref_j 为左值引⽤
int& ref_ret = getVal();  // ref_ret 为左值引用
 
int& ref_j_plus = j + 1;  // ⾮法，左值引⽤不能作⽤于右值
int& ref_const = 0;       // 非法，左值引用不能作用于右值
```

如上例代码所示，**ref_j_plus** 和 **ref_const** 为传统 C++ 中经常使用的左值引用，无法作用于 **j+1** 或 **0** 这样的右值。C++11 引⼊了针对右值的引⽤，即右值引⽤，使用 && 符号声明：

```cpp
int&& ref_k_plus = (i + 1); // ref_k_plus 为右值引用，它绑定了右值 i + 1
int&& ref_k = 0;            // ref_k 为右值引用，它绑定了右值 0 
```

右值引用的特点：

特点一：将死值的续命

```cpp
int getVal() {
  return 1;
}
 
int main() {
    // 这里存在两个值：
    //    1. val(左值)
    //    2. getVal() 返回的临时变量（右值）
    // 其中 getVal() 返回的临时变量赋值给 val 后会被销毁
    int val = getVal();
    // 使用 && 来表明 val 的类型为右值引用
    // 这样 getVal() 返回的临时对象（右值） 将被「续命」
    // 拥有与 val 一样长的生命周期
    int&& val = getVal();
  return 0;
}
```

特点二：在 **⾃动类型推断（如模板函数等）的场景下**，T&& t 是**未定的引⽤类型**，即 t 并⾮⼀定为右值。如果它被左值初始化，那么 t 就为左值。如果它被右值初始化，则它为右值。

```cpp
template<typename T>
void f(T&& t) {}
 
f(10);      // t 为右值
 
int x = 10;
f(x);       // t 为左值
```

**右值引⽤带来的移动语义**

在 C++11 中，像这样「偷⾛」资源的构造函数，称为 「**移动构造函数**」，这种「偷」的⾏为，称为 「**移动语义**」，可理解为「移为⼰⽤」。

```cpp
class HasPtrMem3 {
  public:
    HasPtrMem3() : d(new int(0)) {}
    HasPtrMem3(const HasPtrMem3& h) :  //拷贝构造
        d(new int(*h.d)) {}
    HasPtrMem3(HasPtrMem3&& h) : d(h.d) { //移动构造
      h.d = nullptr; //避免悬浮指针
    }
    ~HasPtrMem3() { delete d; }
    int* d;
};
```

「移动构造函数」中的参数为 HasPtrMem3&& h 为**右值类型[2]**，⽽返回值的临时对象就是右值类型，这也是为什么返回值临时对象能够匹配到「移动构造函数」的原因。

为了实现性能优化，C++11提供了std::move 函数来实现右值引用

```cpp

std::list<std::string> tokens;              // tokens 为左值
  // 省略初始化...
std::list<std::string> t = tokens;          // 这里存在拷贝

 
std::list<std::string> tokens;
std::list<std::string> t = std::move(tokens); // 这里不存在拷贝 
```

std::move 函数实际没有移动任何资源，它唯⼀做的就是**将⼀个左值强制转换成右值引⽤**，从而匹配到「移动构造函数」或「移动赋值运算符」，应⽤移动语义实现资源移动。

右值引⽤**带来的完美转发**

传统 C++ 中右值参数后被转换成左值，即不能按照参数原先的类型进⾏转发

```cpp
template<typename T>
void forwardValue1(T& val) {
  // 右值参数变为左值
  processValue(val);
}
 
template<typename T>
void forwardValue1(const T& val) {
  processValue(val); // 参数都变成常量左值引用了
}
```

C++11 引⼊了 std::forward，它将按照参数的实际类型进⾏转发

```cpp
void processValue(int& a) {
  cout << "lvalue" << endl;
}
 
void processValue(int&& a) {
  cout << "rvalue" << endl;
}
 
template<typename T>
void forwardValue2(T&& val) {
  // 照参数本来的类型进⾏转发
  processValue(std::forward<T>(val));
}
 
int main() {
  int i = 0;
 
  forwardValue2(i); // 传入左值，函数执行输出 lvalue
  forwardValue2(0); // 传入右值，函数执行输出 rvalue
 
  return 0;
}
```

### 有作⽤域枚举

传统C++

```cpp
// Color 下的 BLUE 和 Feeling 下的 BLUE 命名冲突
enum Color { RED, BLUE };
enum Feeling { EXCITED, BLUE };
```

枚举类C++ 11

```cpp
// 定义枚举值为 char 类型的枚举类
enum class Color:char { RED, BLACK };
 
// 使⽤
Color c = Color::RED;
```

### constexpr与字面类型

**constexpr**: 在编译期将表达式或函数编译为常量结果

```cpp
// 修饰变量
constexpr int a = 1 + 2 + 3;
char arr[a]; // 合法，a 是编译期常量
 
// 修饰函数，使函数在编译期会成为常量表达式（如果可以）
// 如果 constexpr 函数返回的值不能在编译器确定，则 constexpr 函数就会退化为运行期函数（这样做的初衷是避免在为编译期和运行期写两份相同代码）
// constexpr 函数的设计其实不够严谨，所以 C++20 引入了 consteval （详见下文 C++20 部分）
// C++11 中，constexpr 修饰的函数只能包含 using 指令、typedef 语句以及 static_assert 
// C++14 实现了对其他语句的支持
constexpr int len_foo_constexpr() {
  return 5;
}
```

### 初始化列表

在 C++98/03 中，普通数组或 **POD 类型** 可以通过初始化列表的⽅式进⾏初始化

```cpp
int arr1[3] = { 1, 2, 3 };
 
long arr2[] = { 1, 3, 2, 4 };
struct A { 
  int x;
  int y;
} a = { 1, 2 };
```

C++11 扩展了「初始化列表」的适⽤范围，使之可以适⽤于所有类型对象的初始化

```cpp
class Dog {
 public:
  Dog(string name, int age) {
    cout << name << " "; cout << age << endl;
  }
};
 
Dog dog1 = {"cat1", 1};
Dog dog2 {"cat2", 2};
```

还可以通过 **std::initializer_list** 来实现更强⼤的「初始化列表」，例如：

```cpp
class Dog {
 public:
  Dog(initializer_list<int> list) {
   for (initializer_list<int>::iterator it = list.begin();
          it != list.end(); ++it) {
      cout << *it << " ";
    } 
    cout << endl;
  }
};
 
Dog dog3 = {1, 2, 3, 4, 5};
```

同时，初始化列表还可以⽤作普通函数的**形参**或**返回值**：

```cpp
// 形参
void watch(Dog dog) {
  cout << "watch" << endl;
}
 
watch({"watch_dog", 4});
 
// Dog 作为返回值
 
getDefaultDog() {
  return {"default", 3};
}
 
getDefaultDog();
```

### 委托与继承的构造函数

**委托构造**：在⼀个构造函数中调⽤同⼀个类的另⼀个构造函数
**继承构造**：在 C++11 之前的 C++ 中，⼦类需要依次声明⽗类拥有的构造函数，并传递相应的初始化参数。C++11 利⽤关键字 using 引⼊了继承构造函数，使⽤⼀⾏语句让编译器⾃动完成上述⼯作。

```cpp
class Parent {
  public:
    int value1;
    int value2;
 
  Parent() {
    value1 = 1;
  }
 
  Parent(int value) : Parent() { // 委托 Parent() 构造函数
    value2 = value;
  }
}
 
class Child : public Parent {
  public: 
    using Parent::Parent;         // 继承构造
}
```

### nullptr

传统 C++ 中 NULL 的定义存在很多缺陷，编译器在实现时常常将其定义为 0，这会导致重载混乱。考虑如下代码；

```cpp
void foo(char*);
void foo(int);
```

当调⽤ foo(NULL) 时将匹配到 foo(int) 函数，这显然会让⼈感到迷惑。

C++11 引⼊了 **nullptr** （类型为 nullptr_t）关键字，以便区分空指针与 0，且 nullptr 能够隐式的转换为任何指针或成员指针的类型。

```cpp
int* nul = nullptr;
cout<<(int)nul<<endl;
//	输出 0
```

### long long

**long**: ⽬标类型将有⾄少 **32 位**的宽度
**long long**: ⽬标类型将有⾄少 **64 位**的宽度

如同 long 类型后缀需要 「l」 或 「L」，long long 类型后缀需要加上「ll」或「LL」。

### char16_t 与 char32_t

C++98 中为了表达 Unicode 字符串，引⼊了 wchar_t 类型，以解决 1 字节的 char 只能 256 个字符的问题。

但是由于 wchar_t 类型在不同平台上实现的长度不同，在代码移植⽅⾯有⼀定的影响。于是 C++11 引⼊ **char16_t** 和 **char32_t**，他们拥有的固定的长度，分别为 **2 个字节**和 **4 个字节**。

**char16_t**: UTF-16 字符表⽰的类型，要求⼤到⾜以表⽰任何 UTF-16 编码单元（ 16 位）。它与 `std::uint_least16_t` 具有相同的⼤⼩、符号性和对齐，但它是独⽴的类型。

**char32_t**: - UTF-32 字符表⽰的类型，要求⼤到⾜以表⽰任何 UTF-32 编码单元（ 32 位）。它与 `std::uint_least32_t` 具有相同的⼤⼩、符号性和对齐，但它是独⽴的类型。

同时 C++11 还定义了 3 个常量字符串前缀：

- u8 代表 UTF-8 编码
- u 代表 UTF-16 编码
- U 代表 UTF-32 编码

```cpp
char16_t UTF16[] = u"中国"; // 使用 UTF-16 编码存储
char32_t UTF16[] = U"中国"; // 使用 UTF-32 编码存储
```

### 类型别名

传统 C++ 中使⽤ typedef 来为类型定义⼀个新的名称，C++11 中我们可以使⽤ using 达到同样的效果，如下所⽰：

```ruby
typedef std::ios_base::fmtflags flags;
using flags = std::ios_base::fmtflags;
```

既然有了 typedef 为什么还引⼊ using？当然是因为 using ⽐起 typedef 还能做更多。

typedef 是只能为「类型」定义新名称，⽽模板则是 「**⽤来产⽣类型**」的，所以以下代码是⾮法的：

```cpp
template<typename T, typename U>
class DogTemplate {
  public: 
    T attr1;
    U aatr2;
};
 
// 不合法
template<typename T>
typedef DogTemplate<std::vector<T>, std::string> DogT;
```

但使⽤ using 则可以为模板定义别名：

```cpp
template<typename T>
using DogT = DogTemplate<std::vector<T>, std::string>;
```

### 变长参数模板

在传统 C++ 中，类模板或函数模板只能接受固定数量的模板参数。

**⽽ C++11 允许任意多个、任意类别的模板参数，同时在定义时⽆需固定参数个数**。如下所⽰：

```cpp
template<typename... T> class DogT;
 
// 传⼊多个不同类型的模板参数
class DogT<int, 
            std::vector<int>,
            std::map<std::string,
            std::vector<int>>> dogT;
 
// 不传⼊参数（ 0 个参数）
class DogT<> nothing;
 
// 第⼀个参数必传，之后为变⻓参数
template<typename require, typename... Args> class CatT;
```

同样的可⽀持模板函数：

```cpp
template<typename... Args>
void my_print(const std::string& str, Args... args) {
  // 使⽤ sizeof... 计算参数个数
  std::cout << sizeof...(args) << std::endl;
}
```

### 推⼴的（⾮平凡）联合体

联合体 Union 为我们提供了在⼀个结构内定义多种不同类型的成员的能⼒，但在传统 C++ 中，并不是所有的数据类型都能成为联合体的数据成员。例如:

```cpp
struct Dog {
  Dog(int a, int b) : age(a), size(b) {}
  int age;
  int size;
}
 
union T {
  // C++11 之前为非法（d 不是 POD 类型）
  // C++11 之后合法
  Dog d;
  int id;
}
```

C++11 **去除**了上述联合体的限制**[3]**，标准规定了**任何⾮引⽤类型都可以成为联合体的数据成员**。

> **[3]** 去除的原因是经过长期的实践证明为了兼容 C 所做的限制没有必要。

### Lambda 表达式

```cpp
// [捕获列表]：捕获外部变量，详见下文
// (参数列表): 函数参数列表
// mutable: 是否可以修改值捕获的外部变量
// 异常属性：exception 异常声明
[捕获列表](参数列表) mutable( 可选 ) 异常属性 -> 返回类型 {
  // 函数体
}
```

捕获列表一般有以下几种类型：

```cpp
// 值捕获：与参数传递中值传递类似，被捕获的变量以值拷贝的方式传入
int a = 1;
auto f1 = [a] () { a+= 1; cout << a << endl;};
a = 3;
f1();
cout << a << endl;

// 加上 & 符号，即可通过引用捕获外部变量：
int a = 1;
// 引用捕获
auto f2 = [&a] () { cout << a << endl; };
a = 3;
f2();

//无需显示列出所有需要捕获的外部变量，通过 [=] 可以通过「值捕获」的方式捕获所有外部变量，[&] 可以通过「引用捕获」的方式捕获所有外部变量：
int a = 1;
auto f3 = [=] { cout << a << endl; };    // 值捕获
f3(); // 输出：1
auto f4 = [&] { cout << a << endl; };    // 引用捕获
a = 2;
f4(); // 输出：2
```

| 捕获形式     | 说明                                                                                          |
| :----------- | :-------------------------------------------------------------------------------------------- |
| []           | 不捕获任何外部变量                                                                            |
| [变量名, …] | 默认以值得形式捕获指定的多个外部变量（用逗号分隔），如果引用捕获，需要显示声明（使用&说明符） |
| [this]       | 以值的形式捕获this指针                                                                        |
| [=]          | 以值的形式捕获所有外部变量                                                                    |
| [&]          | 以引用形式捕获所有外部变量                                                                    |
| [=, &x]      | 变量x以引用形式捕获，其余变量以传值形式捕获                                                   |
| [&, x]       | 变量x以值的形式捕获，其余变量以引用形式捕获                                                   |

### noexcept 说明符与 noexcept 运算符

C++11 将异常的声明简化为以下两种情况：

函数可能抛出任何异常

```csharp
void func(); // 可能抛出异常
```

函数不可能抛出任何异常

```csharp
void func() noexcept; // 不可能抛出异常
```

使⽤ **noexcept** 能够让编译器更好的优化代码，同时 **noexcept** 修饰的函数如果抛出异常将会导致调⽤ `std::terminate()` ⽴即终⽌程序。

noexcept 还可作为运算符使⽤，来判断⼀个表达式是否产⽣异常：

```go
cout << noexcept(func()) << endl;
```

### 范围 for

```cpp
std::vector<int> vec = {1, 2, 3, 4};
for (auto element : vec) {
  std::cout << element << std::endl;  // read only
}
```

### static_assert

我们常⽤ assert，即运⾏时断⾔。但很多事情不该在运⾏时采取判断和检查，而应该在编译期就进⾏严格断⾔，例如数组的长度等。

C++11 引⼊了 static_assert 实现编译期断⾔：

```csharp
static_assert(sizeof(void *) == 4,"64位系统不支持");
```

### 智能指针

C++98 提供了模板类型「auto_ptr」来实现智能指针。auto_ptr 以对象的⽅式管理分配的内存，并在适当的时机释放内存。程序员只需要将 new 操作返回的指针作为 auto_ptr 的初始值即可，如下所⽰：

```csharp
auto_ptr(new int);
```

但 auto_ptr 存在「进⾏拷贝时会将原指针置为 NULL」等缺陷，因此 C++11 引⼊了 **unique_ptr、shared_ptr、 weak_ptr** 三种智能指针。

- **unique_ptr**: unique_ptr 和指定对象的内存空间紧密绑定，不允许与其他 unique_ptr 指针共享同⼀个对象内存。即**内存所有权在同⼀个时间内是唯⼀的**，但所有权却可以通过 #05 条中提及的 move 和移动语义进⾏来实现「所有权」 转移。如下所⽰：

```cpp
unique_ptr<int> p1(new int(111));
 
unique_ptr<int> p2 = p1;        // ⾮法，不可共享内存所有权
unique_ptr<int> p3 = move(p1);  // 合法，移交所有权。p1 将丧失所有权
 
p3.reset();                     // 显式释放内存
```

- **shared_ptr**：与 unique_ptr 相对，可以共享内存所有权，即多个 shared_ptr 可以指向同⼀个对象的内存。同时 shared_ptr 采⽤**引⽤计数法**来判断内存是否还被需要，从⽽判断是否需要进⾏回收。

```cpp
shared_ptr<int> p4(new int(222));
shared_ptr<int> p5 = p4;  // 合法
 
p4.reset();               // 「释放」内存
 
// 由于采⽤引⽤计数法，p4.reset() 仅仅使得引⽤数减⼀
// 所指向的内存由于仍有 p5 所指向，所以不会被回收
// 访问 *p5 是合法且有效的
cout << *p5 << endl;      // 输出 222
```

- **weak_ptr**：weak_ptr 可以指向 shared_ptr 指向的内存，且在必要时可以通过成员 lock 来返回⼀个指向当前内存的 shared_ptr 指针，如果当前内存已经被释放，那么将 lock() 返回 nullptr。⽽另⼀个重点则是 weak_ptr **不参与引⽤计数**。如同⼀个「虚拟指针」⼀样指向 shared_ptr 指向的对象内存，⼀⽅⾯不妨碍内存的释放，另⼀⽅⾯又可以通过 weak_ptr 判断内存是否有效以及是否已经被释放：

```cpp
shared_ptr<int> p6(new int(333));
shared_ptr<int> p7 = p6;
weak_ptr<int> weak_p8 = p7;
 
shared_ptr<int> p9_from_weak_p8 = weak_p8.lock();
 
if (p9_from_weak_p8 != nullptr) {
  cout << "内存有效" << endl;
} else {
  cout << "内存已被释放" << endl;
}
 
p6.reset();
p7.reset(); // weak_p8
 
// 内存已被释放，即使 weak_p8 还「指向」该内存
```

weakptr解决循环引用问题

![](https://img-blog.csdnimg.cn/img_convert/d5cd97f62d2983bb6f83a2fd68e341f7.png)

由于 ObjA 和 ObjB 内部有成员变量相互引⽤，即使将 P1 和 P2 引⽤去除，这两个对象的引⽤计数仍然不为 0。但实际上两个对象已经不可访问，理应被回收。

使⽤ weak_ptr 来实现上⾯两个对象的相互引⽤则可以解决该问题，如下图所⽰：

![](https://img-blog.csdnimg.cn/img_convert/ae15e1ce1334faacd9f0b5060d8287cb.png)

## C++ 14新特性

https://blog.csdn.net/bodybo/article/details/124901297
