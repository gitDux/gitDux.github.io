#include <iostream>
using namespace std;

// 类的内存占用情况
namespace mem{
    class base{
    public:
        virtual void getVal(){
            cout<<"virtual function, base getVal"<<endl;
        }

        virtual void setVal(){
            cout<<"virtual function, base setVal"<<endl;
        }
    private:
        int int1;
        char char1;
        short short1;
    };
}

// 类的虚函数
namespace vir{

    class base{
        public:
            virtual void vir_func(){
                cout<<"virtual function, this is class base"<<endl;
            }
            void func(){
                cout<<"normal function, this is class base"<<endl;
            }
    };

    class A: public base{
        public:
            virtual void vir_func(){
                cout<<"virtual function, this is class A"<<endl;
            }
            void func(){
                cout<<"normal function, this is class A"<<endl;
            }
    };

    class B: public base{
        public:
            virtual void vir_func(){
                cout<<"virtual function, this is class B"<<endl;
            }
            void func(){
                cout<<"normal function, this is class B"<<endl;
            }
    };
}

// 大端小端

namespace ENDIAN{

    union UNI{
        int a;
        char b;
    }uni;

    void IsBigEndian()
    {
            // int a = 0x1234;
            int a = 0x12000034;
            char b =  *(char *)&a;  //通过将int强制类型转换成char单字节，通过判断起始存储位置。即等于 取b等于a的低地址部分

            if( b == 0x12)
                cout<<"big endian"<<endl;
            if( b == 0x34)
                cout<<"small endian"<<endl;

            return;
    }

    void IsBigEndian_union()
    {
            // int a = 0x1234;
            // char b =  *(char *)&a;  //通过将int强制类型转换成char单字节，通过判断起始存储位置。即等于 取b等于a的低地址部分
            uni.a = 0x12000034;

            if( uni.b == 0x12)
                cout<<"big endian"<<endl;
            if( uni.b == 0x34)
                cout<<"small endian"<<endl;

            return;
    }
}


class ClassA {
  public:
    virtual ~ClassA(){};
    virtual void FunctionA(){};
};
class ClassB {
  public:
    virtual void FunctionB(){};
};
class ClassC : public ClassA, public ClassB {
  public:
};
 



int main(){


    vir::base * Base = new vir::base();
    vir::base * a = new vir::A();
    vir::base * b = new vir::B();
    Base->func(); a->func(); b->func();
    cout<<"*****"<<endl;
    Base->vir_func(); a->vir_func(); b->vir_func();
	cout<<"*****"<<endl;
    ((vir::A*)b)->vir_func();
    ((vir::A*)b)->func();

    cout<<"*****"<<endl;
    typedef void (*Fun)();
    cout<<"address of b: "<< *(int*)b<<endl;
    Fun fun = (Fun)(*(int*)*(int*)b);
    fun();

    cout<<"*****"<<endl;
    ENDIAN::IsBigEndian();

    cout<<"*****"<<endl;
    ClassC aObject;
    cout<<(ClassA*)&aObject<<endl;
    cout<<(ClassB*)&aObject<<endl;
    cout<<(ClassC*)&aObject<<endl;

    cout<<"*****"<<endl;
    bool boolvector[10];
    bool *p = boolvector;
    cout<<p<<endl;
    cout<<++p<<endl;
    
    cout<<"******"<<endl;
    int* nul = nullptr;

    cout<<(int)nul+1<<u"阿斯顿"<<endl;

    cout<<"*****"<<endl;

    return 0;

}


