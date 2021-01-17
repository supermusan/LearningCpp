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
    ```cpp
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
