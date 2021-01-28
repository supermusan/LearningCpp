## P1 导读
<br><br>

## P2 convert function 转换函数
```c++
class Fraction{ //分数
    public Fraction(int num, int den=1)
       : m_numerator(num), m_denominator(den) {}
    operator double() const{ // double转换函数
        return (double) (m_numerator/m_denominator);
    }
    private:
    int m_numerator; // 分子
    int m_denominator; // 分母
}
{
    Fraction f(3,5);
    double d = 4 + f; //调用 operator double() 将f转换为double
}
```
<br><br>

## P2 non-explicit one augment constructor
1. one augment,指一个实参，如下例子中den=1有默认实参，num是one augment
2. 构造函数默认是non-explicit的，explicit关键字禁止隐式转换
3. 若上章的conversion function 和 下面的non-explicit one augment constructor 并存，若调用 ```double d = f+4``` 会二义报错
```c++
class Fraction{ //分数
    public Fraction(int num, int den=1)
       : m_numerator(num), m_denominator(den) {}
    Fraction operator+(const Fraction& f){
        return Fraction(...);
    }
    }
    private:
    int m_numerator; // 分子
    int m_denominator; // 分母
}
{
    Fraction f(3,5);
    double d = f+4; //调用 non-expilcit ctor将4转为Fraction(4,1),然后调用operator+
}
```

## P3  pointer-like classes
1. 关于智能指针
    ```c++
    template<class T>
    class shared_ptr{
        public:
            T& operator*() const {return *px;}
            T* operator->() const {return px;} //把指针对象本身传回去
            shared_ptr(T* p): px(p) {}
        private:
            T* px;
            long* pn;
            ...
    }
    {
        shared_ptr<Foo> sp(new Foo);
        Foo f(*sp);
        sp->method(); //=>> px->method();箭头符号会用一直作用下去
    }

    ```
2. 关于迭代器,看视频比较清楚
   ```c++
   template<class T, class Ref, class Ptr>
   struct __list_iterator{
       typedef __list_iterator<T,Ref,Ptr> self;
       typedef Ptr pointer;
       ...
   }
   ```
<br><br>

## P5 function-like classes
1. 所谓仿函数 class 中重载  operator()
<br><br>

## P6 namespace 经验谈
<br><br>

## P7 class template 类模板
1. 模板表示中template和class共通
```c++
template<typename T>
class complex{
    public:
    complex(T r=0,T i=0);
    ...
}
```
<br><br>

## P8 function template 函数模板
```c++
template<class T>
inline
const T& min(const T& a, const T& b){
    return b<a?b:a;
}
```
<br><br>

## P9 member template 成员模板
1. 在模板里头，同时自己又是模板
<br><br>

## P10 specialization 模板特化
1. 定义模板中的某些特例
```c++
template<class key>
struct hash{};

template<>
struct hash<char>{
    size_t operator()(char x) const {return x};
}
{
    hash<long>()(1000);
}

```
<br><br>

## P11 partial specialization 模板偏特化
1. 个数上的偏
   ```c++
   template<typename T, typename Alloc=...>
   class vector{};
   template<typename Alloc=...> 
   class vector<bool, Alloc>{};//绑定第一个为bool值
   ```
2. 范围上的偏
   ```c++
   template<typename T>
   class C{ };
   template<typename T>
   class C<T*>{ }; //绑定为一个指针
   ```
<br><br>

## P12 template template parameter 模板模板参数
```c++
template<typename T, 
        template<typename T>
            class Container>
        >
class XCls
{
    private：
        Container<T> c;
    public:
    ...
};

template<typename T>
using Lst = list<T, allocator<T>>;

{
    XCls<string, list> mylst1; //错误，因为容器有第二模板参数，这种语法通不过
    XCls<string, Lst> mylst2; 
}
```

