// 程序需要在多个对象间共享数据
#include<iostream>
#include<memory>
#include<string>
#include<vector>
using namespace std;
class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;
    public:
        typedef vector<string>::size_type size_type;
        StrBlob();
        StrBlob(initializer_list<string> il);
        StrBlobPtr begin();
        StrBlobPtr end();
        size_type size() const {return data->size();}
        bool empty() const {return data->empty();}
        void push_back(const string &str) {data->push_back(str);}
        void pop_back();
        string& front();
        string& back();
        const string& front() const;
        const string& back() const;
        const shared_ptr<vector<string>>& getdata() const {return data;}
    private:
        shared_ptr<vector<string>> data;
        void check(size_type i, const string &msg) const;
};

// 对于访问一个不存在元素的尝试，StrBlobPtr抛出一个异常
class StrBlobPtr{
    public:
        StrBlobPtr(): curr(0) {}
        StrBlobPtr(StrBlob &a, size_t sz=0):
            wptr(a.data), curr(sz) {}
        string& deref() const;
        StrBlobPtr& incr(); // 前缀递增
    private:
        // 若检查成功，check返回一个指向vector的shared_ptr
        shared_ptr<vector<string>> check(size_t, const string&) const;
        weak_ptr<vector<string>> wptr;
        size_t curr; //在数组中的当前位置
};

StrBlob::StrBlob(): data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {}
void StrBlob::check(size_type i, const string &msg) const{
    if (i>=data->size())
        throw out_of_range(msg);
}
void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
string& StrBlob::front(){
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}
const string& StrBlob::front() const{
    check(0, "front on empty StrBlob");
    return data->front();
}
const string& StrBlob::back() const{
    check(0, "back on empty StrBlob");
    return data->back();
}
StrBlobPtr StrBlob::begin() {return StrBlobPtr(*this);}
StrBlobPtr StrBlob::end() {
    auto ret=StrBlobPtr(*this, data->size());
    return ret;
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const{
    auto ret = wptr.lock();
    if(!ret)
        throw runtime_error("unbound StrBlobPtr");
    if(i>= ret->size())
        throw out_of_range(msg);
    return ret;
}
string& StrBlobPtr::deref() const{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr(){
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

int main(){
    StrBlob sb1{"This","is","a","test","sentence"};
    {
        StrBlob sb2(sb1);
        cout << sb1.getdata() << " " << sb2.getdata() << " " << sb1.getdata().use_count() << " " << sb2.getdata().use_count() << endl;
    }
    cout << sb1.getdata() << " " << sb1.getdata().use_count() << endl;
    const StrBlob sb3{"This","is","a","test","sentence"};
    cout << sb1.front() << " " << sb3.front() << endl;
    sb1.push_back("haha");
    cout << sb1.back() << endl;

    auto sb1_b = sb1.begin();
    cout << sb1_b.deref().back() << endl;

    return 0;
}