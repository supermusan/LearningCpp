#include<iostream>
#include<string>
#include<vector>
#include"Sales_data.h"
// 每个类定义了唯一的类型，对于两个类来说，即使他们的成员函数完全一样，这两个类也是不同的两个类型
int main(){
    Sales_data total;
    if(read(cin, total)){
        Sales_data trans;
        while(read(cin, trans)){
            if(total.isbn()==trans.isbn())
                total.combine(trans);
            else
            {
                print(cout, total) << endl;
                total = trans;
            } 
        }
        print(cout, total) << endl;
    }
    else
    {
        cerr << "No Data?!" << endl;
    }
    return 0;
}