## P1 C++编译简介
1. [c++98]\
<br>

## P2 头文件与类的声明
1. 防卫式声明 (guard)
    ```cpp
    //complex.h
    #ifndef __COMPLEX__\
    #define __COMPLEX__\
    ...\
    #endif
    ```
2. template
    ```cpp
    template<typename T>
    class complex{
        // ...
        private:
            T re, im;
    }
    {
        complex<double> c1(2.1,1.5);
        complex<int> c2(2,6)
    }
    ```
<br>

## P3 构造函数
1. inline(内联)函数
   - 在类内定义默认是inline函数
   - 类外部可以加inline关键字定义未inline函数
2. access level 访问级别
   - private, public, project
3. 构造函数
   - 默认实参
     ```cpp
     class complex{
     public:
       complex (double r=0, double i = 0): re(r), im(i) {}
       // ...
     }
     ```
     构造函数初始化，不要在{}中赋值
   - 不带指针的类多半不用写析构函数
   - 多个构造函数，重载
<br><br>

## P4 参数传递与返回值
1. 常量成员函数 const
   - 函数后加const，不允许改变对象的数据
      ```c++
      class complex{
        public:
            complex (double r=0, double i = 0): re(r), im(i) {}
            double real () const {return re;}
        // ...
      }
      {
        const complex c1(2,1);
        c1.real(); // 若成员函数real()未加const，不但能对const对象c1调用该成员函数
      }
      ```
2. 参数传递 [pass by value vs. pass by reference (to const)]
   - 参数尽量传引用，尽量返回引用
3. 友元
   - 自由取得friend的private成员
   - 相同class的各个object互为friends
4. 不能 return by reference 的情况
   - 函数中声明的变量需要返回值，因为离开函数域该变量被销毁
<br><br>

## P5 操作符重载与临时对象
1. 操作符重载——成员函数
   - 二目操作符左边的值为操作符调用者 c2+=c1 c2为调用者
   - return by reference 语法分析
      ```cpp
      inline complex& 
      __doapl(complex* this, const complex& r){
        ...
        return *ths;
      }
      ```
      传递者无需知道接收者是以reference形式接收
2. 头文件布局
    ```cpp
    //complex.h
    #ifndef __COMPLEX__\
    #define __COMPLEX__\
    
    #include<cmath>

    // 前置声明
    class ostream;
    class complex;
    complex&
      __doapl(complex* ths, const complex& r);

    // 类声明
    class complex{
        ...
    };

    // 类定义
    complex::function ...
    #endif
    ```
3. 操作符重载——非成员函数
   ```cpp
   inline complex
   operator + (const complex& x, const complex& y){...}
   inline complex
   operator + (const complex& x, double y){...}
   inline complex
   operator + (double x, const complex& y){...}

   ```
   上面的函数返回value，因为他们的返回是 local object
<br><br>

## P6 复习 Complex 类的实现过程
1. 注意
   - 防卫式函数定义
   - 数据放在private中
   - 构造函数要用初值列【initializer list】不要赋值
<br><br>

## P7 三大函数：拷贝构造、拷贝赋值、析构
1. class 里面有指针，多半要动态分配内存，析构函数中要释放掉内存
   ```c++
   class String{
        public:
            String(const char* cstr = 0);
            String(const String& str);
            String& operator=(const String& str);
            ~String();
            char* get_c_str() const {return m_data;}
        private:
            char* m_data;
   }

   inline
   String::String(const char* cstr=0){
       if(cstr){
           m_data = new char[strlen(cstr)+1];
           strcpy(m_data, cstr);
       }
       else{
           m_data = new char[1];
           *m_data = '\0';
       }
   }

   inline
   String::~String(){
       delete[] m_data;
   }

   {
       String s1();
       String s2("hello");
       String *p = new String("hello");
       delete p;
   }
   ```
2. class with pointer member 必须有copy ctor 和 copy op=
   ```c++
   inline
   String::String(const String& str){
       m_data = new char[strlen(str.m_data)+1]
       strcpy(m_data, str.m_data)
   }

   inline
   String& String::operator=(const String& str){
       if(this==&str) // 检测自我赋值
          return *this;
       delete[] m_data;
       m_data = new char[strlen(str.m_data)+1];
       strcpy(m_data, str._mdata);
       return *this;
   }

   {
       String s1("hello");
       String s2(s1);
       s3 = s1;
   }
   ```
<br><br>

## P8 堆、栈与内存管理
1. output 函数,不能写成成员函数，若写为成员函数则String对象在<<运算符左边，与常规习惯不符
   ```c++
   #include<iostream>
   ostream& operator<<(ostream& os, const String& str){
       os << str.get_c_str();
       return os;
   }
   ```
2. stack & heap & static objects & global objects
3. new: 先分配memory再调用ctor
   ```c++
   Complex* pc = new Complex(1,2);
   //编译器转化为
   Complex *pc;
   void* mem = operator new(sizeof(Complex)); //分配没存，operator new 用 malloc() 实现
   pc = static_cast<Complex*>(mem); //类型转换
   pc->Complex::Cmoplex(1,2); //构造函数
   ```
4. delete:先调用析构函数，在释放内存
   ```c++
   delete ps;
   //编译器转化为
   String::~String(ps); //析构函数
   operator delete(ps); //释放内存，operator delete 内部调用free()
   ```
5. 动态分配所得的内存块和array，详见视频
   - array new (new arr[]) 一定要搭配 array delete (delete[] arr)
   - delete[] p 会对数组中每个对象调用析构函数，而 delete p 只调用一次析构函数
<br><br>

## P9 复习String类的实现过程
<br><br>

## P10 拓展补充
1. static
   - 成员函数通过this pointer取得相应的对象，处理对应的数据
   - static 成员函数脱离对象
   - static 变量数据一定要在class外部定义该静态变量
        ```c++
        class Account{
            public:
                static double m_rate;
                static void set_rate(const double& x){m_rate = x;}
        };
        double Account::m_rate = 8.0; //定义该静态变量，分配内存
        int main(){
            Account::set_rate(5.0);
            Account a;
            a.set_rate(7.0);
        }
        ```
   - 把ctors放在private区的情况
2. cout
3. template
4. function template
   ```c++
   template <class T>
   inline T& min(const T& a, const T& b){
       return b < a ? b : a;
   }
   ```
5. namespace
<br><br>

## P11 组合与继承
1. Adapter 适配器 设计模式
2. Composition 关系下的构造和析构
   - 构造由内而外
   - 析构由外而内
3. Delegation 委托 【Composition by reference】
4. inheritance 继承
   - base class 的 dtor（析构函数） 必须是 virtual
   - 构造由内而外，析构由外而内
<br><br>

## P12 虚函数与多态 (详见视频)
1. 函数的继承，继承的是调用权
2. virtual 
   - non-virtual 不希望 derived class 覆盖它
   - virtual 希望 derived class 覆盖它，且你有默认定义
      ```c++
      vitual void draw() const;
      ```
   - pure virtual 希望 derived class 一定要覆盖它，没有默认定义
      ```c++
      vitual void draw() const = 0;
      ```
3. Inheritance with vitual
   - 子类可以调用父类的函数
   - Template Method 设计模式
4. Delegation + Inheritance
   - Subject-Observer 设计模式
<br><br>

## P13 委托相关设计
**设计模式**
1. Adapter
2. Handle-Body
3. Template Method
4. Observer
5. Composite
6. Prototype

   


