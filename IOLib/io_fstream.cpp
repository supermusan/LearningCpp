#include<iostream> //读写流
#include<fstream> //读写文件
#include<sstream> //读写string
//ifstream istringstream 继承自 istream
//ofstream ostringstream 继承自 ostream
#include<string>
#include<vector>
using namespace std;

istream &read(istream &is, vector<string> &vec){
    string temp;
    is >> temp;
    cout << temp;
    vec.push_back(temp);
    return is;
}

ostream &print(ostream &os, const vector<string> &vec){
    os << vec.back();
    return os;
}

int main(int argc, char* argv[]){
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    vector<string> lines;
    /*
    while(read(input, lines)){
        print(output, lines) << endl;
    }*/
    lines.push_back("");
    /*
    while(getline(input, *(--lines.end()))){
        print(output, lines) << endl;
        lines.push_back("");
    }*/
    ofstream out;
    out.open(static_cast<string>(argv[1]) + ".copy");
    while(getline(input, *(--lines.end()))){
        print(out, lines) << endl;
        lines.push_back("");
    }    
    input.close();
    output.close();
    out.close();
    // 若不截断，需要显示指定 ofstream::app
    return 0;
}