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
<br><br>

## P13 关于C++标准库
1. 快乐地使用标准库哦
<br><br>

## P14 三个主题
1. variadic template 数量不定的模板参数
   ```c++
   template<typename T, typename... Types>
   void print(const T& firstArg, const Types&... args){
       cout << firstArg << endl;
       print(args...); // 递归调用，把args中的参数一个一个打印出来
   }
   ```
2. auto
3. range-base for
   ```c++
   for(decl:coll){statement}

   for(int i:{1,2,3,4,5,6,7,8,9}){
       cout << i << endl;
   }
   ```
<br><br>

## P15 reference
1. 指针指向一个对象，引用代表一个对象，将r看作这个对象
2. 引用代表了一个对象，就绑定了，再也不能代表其他对象了。对一个已绑定的指针进行赋值操作，会更改其代表的对象
3. object 和其 reference 显示的大小(sizeof())地址(&)都相同，不过这是假象。因为对引用的操作实际是操作了其代表的对象。
4. 传值和传引用调用端接口相同
   ```c++
   void func1(Cls* pobj){pobj->xxx();}
   void func2(Cls pobj){pobj.xxx();}
   void func3(Cls& pobj){pobj.xxx();}

   Cls obj;
   func1(&obj); //接口不同
   func2(obj);
   func3(obj);
   ```
5. 以下被视为 "same signature" 不能并存,因为他们的的调用端相同，会产生二义性
   ```c++
   double imag(const double& im) {...}
   double imag(const double im) {...}
   ```
<br><br>

## P16 复合&继承关系下的构造和析构
1. inheritance 关系下的构造和析构
   - 子类对象(外)包含父类成分(内)
   - 构造由内而外，析构由外而内
2. inheritance + composition 关系下的构造和析构
   - 构造由内而外，先调用父类base，在调用component part
   - 析构由外而内，先调用component part，在调用父类base
   - base和 component part 顺序可能跟编译器有关，先后不影响
<br><br>

## P17 关于 vptr（虚函数） 和 vtbl（虚表） 具体看视频
1. 虚函数的调用流程，动态绑定
   - 虚指针指向一个指针表（虚表），表中指针指向虚函数
   - 容器放父类指针，可以用来存储一组子类的指针
   - 这种动态绑定的用法叫做多态
<br><br>