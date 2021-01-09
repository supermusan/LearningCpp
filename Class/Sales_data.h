#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Sales_data{
    friend istream& read(istream&, Sales_data&);
    friend ostream& print(ostream&, Sales_data&);
    public:
        Sales_data() = default;
        Sales_data(const string &s): bookNo(s){}
        Sales_data(const string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p) {}
        Sales_data(istream &);
        string isbn() const {return bookNo;}
        void combine(const Sales_data&);
        double avg_price() const;
    private:
        string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};
Sales_data::Sales_data(istream &is){
    read(is, *this);
}
void Sales_data::combine(const Sales_data& item){
    this->units_sold += item.units_sold;
    this->revenue += item.revenue;
}
double Sales_data::avg_price() const{
    if(this->units_sold)
        return this->revenue / this->units_sold;
    else
        return 0.0;
}
istream& read(istream& is, Sales_data &item){
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
ostream& print(ostream& os, Sales_data &item){
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "<< item.avg_price();
    return os;
}
Sales_data add(const Sales_data&, const Sales_data&);