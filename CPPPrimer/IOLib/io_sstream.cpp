#include<iostream> //读写流
#include<fstream> //读写文件
#include<sstream> //读写string
//ifstream istringstream 继承自 istream
//ofstream ostringstream 继承自 ostream
#include<string>
#include<vector>
using namespace std;

int main(int argc, char* argv[]){
    /*
    sstream strm;
    sstream strm(s);
    strm.str(); 返回strm的拷贝
    strm.str(s); 将 stream s 拷贝到 strm，返回 void
    */
    string str("This is a test sentence."), out;
    istringstream ssin(str);
    ostringstream ssout;
    string temp;
    while(ssin >> temp){
    // cout << ssin << endl;
    ssout << temp << " ";
    }
    cout << ssout.str() << endl;



    return 0;
}