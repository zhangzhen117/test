#ifndef SALES_DATA
#define SALES_DATA
#include<iostream>
#include<string>
using namespace std;


class Sales_data{
friend Sales_data add(const Sales_data&, const Sales_data&);
friend ostream &print(ostream&,const Sales_data&);
friend istream &read(istream&, Sales_data&);
public:
    Sales_data()=default;
    Sales_data(const string &s):bookNo(s) {cout<<"using string to init"<<endl;}
    Sales_data(const string &s,unsigned n, double p):
            bookNo(s),units_sold(n),revenue(p*n) 
            {cout<<"using string, unsigned, and double to init"<<endl;}
    Sales_data(istream &);
    string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
private:
    inline double avg_price() const;
    double revenue=0;
    unsigned units_sold=0;
    string bookNo;
};

Sales_data add(const Sales_data&, const Sales_data&);
ostream &print(ostream&,const Sales_data&);
istream &read(istream&, Sales_data&);

Sales_data::Sales_data(istream &is){
    read(is,*this);
    cout<<"using input to init"<<endl;
}


double Sales_data::avg_price() const {
    if (units_sold)
        return revenue/units_sold;
    else
        return 0;
}


Sales_data& Sales_data::combine(const Sales_data&rhs){
    units_sold+=rhs.units_sold;
    revenue+=rhs.revenue;
    return *this;
}


istream &read(istream& is, Sales_data& item){
    double price=0;
    cout<<"Enter bookNo, units_sold, and price:" <<endl;
    is>>item.bookNo>>item.units_sold>>price;
    item.revenue=price*item.units_sold;
    return is;
}


ostream &print(ostream& os,const Sales_data& item){
    os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "
        <<item.avg_price();
    return os;
}


Sales_data add(const Sales_data& lhs, const Sales_data& rhs){
    Sales_data sum=lhs;
    sum.combine(rhs);
    return sum;
}

class Quote{
public:
    Quote()=default;
    Quote(const string &book, double sales_price):
            bookNo(book), price(sales_price){}
    string isbn() const{return bookNo;}
    virtual double net_price(size_t n) const
            {return n*price;}
    virtual ~Quote()=default;
    virtual void debug() const{
        cout<<"class: Quote, ISBN: "<<isbn()<<endl;}
private:
    string bookNo;
protected:    
    double price=0.0;
};

class Disc_quote:public Quote{
public:
    Disc_quote()=default;
    Disc_quote(const string book, double price, size_t qty, double disc):
            Quote(book, price), quantity(qty), discount(disc){}
    double net_price(size_t) const=0;
protected:
    size_t quantity=0;
    double discount=0.0;
};

class Bulk_quote:public Disc_quote{
public:
    Bulk_quote()=default;
    Bulk_quote(const string& book, double p, size_t qty, double disc):
            Disc_quote(book, p, qty, disc){}
    double net_price(size_t) const override;
    virtual void debug() const override{
        cout<<"class: Bulk_quote, ISBN: "<<isbn()<<endl;}
};
double Bulk_quote::net_price(size_t cnt) const{
    if(cnt>quantity)
        return cnt*(1-discount)*price;
    else
        return cnt*price;
}

double print_total(ostream &os, const Quote &item, size_t n){
    double ret=item.net_price(n);
    os<<"ISBN: "<<item.isbn()<<" # sold: "<<n<<" total due: "<<ret<<endl;
    return ret;
}
#endif
