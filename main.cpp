#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "SeqList.h"
#include "DynamicList.h"
#include "StaticList.h"

using namespace std;
using namespace MyDataStructLib;

//================== 智能指针类  =========================
class BaseSmartPointer
{
public:
    BaseSmartPointer()
    {
        cout << "BaseSmartPointer()" << endl;
    }
    ~BaseSmartPointer()
    {
        cout << "~BaseSmartPointer()" << endl;
    }
};

void TestSmartPointer()
{
    SmartPointer<BaseSmartPointer> p = new BaseSmartPointer();
    cout << "p is null ? : "<< p.isNull() << endl ;
    cout << "p get: "<< p.get() << endl ;

     SmartPointer<BaseSmartPointer> nsp ;

     nsp = p ;
     cout << "After nsp = p " << endl;
     cout << "p is null ? : "<< p.isNull() << endl ;
     cout << "p get: "<< p.get() << endl ;
     cout << "nsp is null ? : "<< nsp.isNull() << endl ;
     cout << "nsp get: "<< nsp.get() << endl ;
}

//================== 异常类     =========================
void TestException()
{
    try{
        THROW_EXCEPTION( ArithmeticException , "myException:");
        //throw Exception("Exception", __FILE__ , __LINE__);
    }
    catch(const ArithmeticException& e)
    {
        cout << "===in catch(const Exception& e)===" << endl;
        cout << e.message()  << endl ;
        cout << e.location() << endl;
    }
    catch(const Exception& e)
    {
        cout << "===in catch(const Exception& e)===" << endl;
        cout << e.message()  << endl ;
        cout << e.location() << endl;
    }
}

//================== 顶层父类   =========================
class Child1 : public Object
{
public:
    int i ;
    int j ;
};
class Child2 : public Child1
{
public:
    int k ; // 因为有一个虚函数列表，会产生一个虚函数列表的指针
};

void TestObject()
{
    cout << endl;
    Object* obj1 = new Child1();
    Object* obj2 = new Child2();

    delete obj1;
    delete obj2;
}

void TestList()
{
    List<int>* a = NULL ;
}

void TestSeqList()
{
    SeqList<int>* b ; // 不可以定义对象，但是可以定义指针
}

void TestDynamicList()
{
    DynamicList<int> l(5);

    cout << endl ;
    for ( int i = 0 ; i < l.capacity() ; i++ )
    {
        l.insert(i,0);
    }

    for ( int i = 0 ; i < l.length() ; i++ )
    {
        cout << l[i] << endl ;
    }

    cout << endl;

    l.resize(15);
    for ( int i = 0 ; i < l.length() ; i++ )
    {
        cout << l[i] << endl ;
    }

}

int main()
{
    //TestSmartPointer();
    //TestException();
    //TestObject();
    TestDynamicList();

    return 0;
}

