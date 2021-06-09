#include "ZHEN.h"
class StrBlobPtr;

class StrBlob{
friend class StrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();
    std::string& front() const;
    std::string& back() const;
    std::string& front();
    std::string& back();
    StrBlobPtr begin();
    StrBlobPtr begin()const;
    StrBlobPtr end(); 
    StrBlobPtr end()const; 
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i,const std::string &msg) const;
};

StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
void StrBlob::check(size_type i,const string & msg) const{
    if(i>=data->size())
        throw out_of_range(msg);
}
void StrBlob::pop_back(){
    check(0,"pop_back on empty StrBlob");
    data->pop_back();
}
string& StrBlob::front() const{
    check(0,"front on empty StrBlob");
    return data->front();
}
string& StrBlob::front(){
    check(0,"front on empty StrBlob");
    return data->front();
}
string& StrBlob::back() const{
    check(0,"back on empty StrBlob");
    return data->back();
}
string& StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back();
}

class StrBlobPtr{
public:
    StrBlobPtr():curr(0) {}
    StrBlobPtr(StrBlob &,size_t);
    StrBlobPtr(const StrBlob &,size_t);
    string& deref() const;
    StrBlobPtr& incr();
private:
    shared_ptr<vector<string>> check(size_t,const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

StrBlobPtr::StrBlobPtr(StrBlob &a,size_t sz=0):wptr(a.data),curr(sz){}
StrBlobPtr::StrBlobPtr(const StrBlob &a,size_t sz=0):wptr(a.data),curr(sz){}
shared_ptr<vector<string>> StrBlobPtr::check(size_t i,const string& msg) const{
    auto ret=wptr.lock();
    if(!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i>=ret->size())
        throw out_of_range(msg);
    return ret;
}
string& StrBlobPtr::deref() const{
    auto p=check(curr,"dereference past end");
    return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr(){
    check(curr,"increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr StrBlob::begin() {return StrBlobPtr(*this);}
StrBlobPtr StrBlob::end() {
    auto ret=StrBlobPtr(*this,data->size());
    return ret;
}
StrBlobPtr StrBlob::begin() const{return StrBlobPtr(*this);}
StrBlobPtr StrBlob::end() const{
    auto ret=StrBlobPtr(*this,data->size());
    return ret;
}

int main(){
    const StrBlob blob{"hello","world"};
    auto ptr=blob.begin();
    for(int i=0;i!=blob.size();++i){
        cout<<ptr.deref()<<"\n";
        ptr.incr();
    }
    return 0;
}
