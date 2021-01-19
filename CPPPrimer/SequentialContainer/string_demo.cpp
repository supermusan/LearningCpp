#include<string>
#include<iostream>
#include<typeinfo>
// string 和 vector 相似的容器，用于保存字符，随机访问快，尾部插入删除快
using namespace std;
int main(int argc, char *argv[]){
    // 构造函数
    string str1;
    str1.push_back('1'); //尾插
    str1.push_back('b');
    cout << str1 << endl;
    string str2(str1);
    cout << str2 << endl;
    string str3(str1.begin(), --str1.end());
    cout << str3 << endl;
    string str4{'a','b','c','d'};
    cout << str4 << endl;
    string str5 = str4;
    cout << str5 << endl;
    string str6(5,'a');
    cout << str6 << endl;

    // 添加元素
    string str = "abcd";
    str.push_back('e');
    str.insert(str.insert(str.insert(str.begin(),'1'),'0'), str6.begin(), str6.end()); //返回一个迭代器指向插入的元素
    cout << str << endl;
    
    // 访问元素
    /*
    c.back()
    c.front()
    c[n]
    c.at(n) 若越界会抛出异常
    返回的都是引用
    */
    str.front() = '#';
    // 若用auto,且需要改变元素,要显示定义为引用
    auto &v = str.back();
    v = '!'; //改变元素
    auto v2 = str.back();
    v2 = '?'; //不改变元素
    cout << str << endl;
    try{
        str.at(100);
    }
    catch(exception& e){
        cout << e.what() << endl;
    }

    // 删除元素
    /*
    c.pop_back()
    c.erase(p)
    c.erase(b,e)
    c.clear()
    */
    str.pop_back();
    cout << str << endl;
    str.erase(str.begin(), str.begin()+2);
    cout << str << endl; 
    str.erase(--str.end());
    cout << str << endl;
    str.clear();
    if(str.empty())
        cout << "Empty String." << endl;
    else
        cout << str << endl;

    // String 特殊操作
    // 构造函数
    /*
    string s(cp, n) // s是cp指向的数组中前n个字符的拷贝
    string s(s2, pos2) 
    string s(s2, pos2, len2) //从s2的pos2坐标处开始拷贝(len2个字符)
    */
    char *str_1 = "Test sentence 1.";
    char str_2[] = "Test sentence 2.";
    string str7(str_1, 10);
    cout << str7 << endl;
    string str8(str_2, 5);
    cout << str8 << endl;
    string str9(str7, 1);
    string str10(str7, 2, 5);
    cout << str9 << endl << str10 << endl;

    // substr
    /*
    s.substr(pos, n) [default: pos=0 n=s.size()-pos]
    */
    cout << str7.substr(2, 5) << endl;

    // 改变string的其他方法
    /*
    s.insert(pos, args)
    s.erase(pos, len)
    s.assign(args)
    s.append(args)
    s.replace(range, args)
    args可能是下面形式，replace、append可以使用所有形式
    str 与 s 不同，b e不能指向 s
    str
    str, pos, len
    cp, len
    cp
    n, c
    b, e
    列表初始化
    */
    string str_change("abcde");
    str_change.insert(str_change.size(), 5, '!');
    cout << str_change << endl;
    str_change.erase(str_change.size()-5, 5);
    cout << str_change << endl;
    const char *cp = "This is a C-styled string.";
    str_change.assign(cp, 5);
    cout << str_change << endl;
    str_change.insert(str_change.size(), cp+5);
    cout << str_change << endl;
    str_change.insert(0, "Hello ");
    cout << str_change << endl;
    str_change.insert(0, "Hello", 0, 3);
    cout << str_change << endl;

    // append 和 replace
    /*
    append 是在末尾插入的简写形式
    replace 是调用erase和insert的简写形式
    s.append(args)
    s.replace(range, args) // 删除s中范围range中的字符，替换为args指定的字符
    range : (pos, len) / (b, e)
    */
    str_change.append("  Hi!",1,4);
    cout << str_change << endl;
    str_change.replace(3, 5, "lo");
    cout << str_change << endl;

    // string 搜索操作
    /*
    s.find(args) 查找 args 第一次出现的位置
    s.rfind(args)
    s.find_first_of(args) 查找 args 中任何一个字符第一次出现的位置
    s.find_last_of(args)
    s.find_first_not_of(args) 查找第一个不在args中出现的字符
    s.find_last_not_of(args)
    args:
    c, pos
    s2, pos
    cp, pos
    cp, pos, n
    */
    const string numbers("0123456789");
    string str_find("Hahaha123H");
    cout << str_find.find_first_of(numbers, 4) << endl; 
    cout << str_find.find_first_not_of(numbers, 4) << endl; 
    cout << str_find.find_last_of(numbers, 7) << endl; 
    cout << str_find.find_last_not_of(numbers, 7) << endl; 
    cout << str_find.find("ha") << endl;
    cout << str_find.find("ha", 3) << endl;

    // compare
    /*
    s1.compare(s2)
    s1.compare(pos1, n1, s2)
    s1.compare(pos1, n1, s2, pos2, n2)
    */

    // 数值转换
    /*
    to_string(val) // 返回val的string形式
    stoi(s,p,b) \\ b表示进制，p表示s中第一个非数字字符下标，默认十进制
    ...
    stof(s,p)
    */ 
    cout << to_string(10) << " " << to_string(10.1) << endl;
    string snum("10.1");
    int inum = stoi(snum);
    long lnum = stol(snum);
    unsigned long ulnum = stoul(snum);
    long long llnum =stoll(snum);
    unsigned long long ullnum = stoull(snum);
    float fnum = stof(snum);
    double dnum = stod(snum);
    long double ldnum = stold(snum);
    cout << typeid(inum).name() << " " << typeid(lnum).name() << " " << typeid(ulnum).name() << " " << typeid(llnum).name() << " " << typeid(fnum).name() << " " << typeid(dnum).name() << " " << typeid(ldnum).name() << endl;
    cout << inum << " " << lnum << " " << ulnum << " " << llnum << " " << fnum << " " << dnum << " " << ldnum << endl;

    
    return 0;
}


