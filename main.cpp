#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "SeqList.h"
#include "DynamicList.h"
#include "StaticList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"

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

/*
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
*/

void TestStaticArray()
{
    StaticArray<int,5> a;

    for ( int i = 0 ; i < a.length() ; i++ )
    {
        a[i] = i * i ;
    }
    cout << " Read from StaticArray a :" << endl ;
    for ( int i = 0 ; i < a.length() ; i++ )
    {
        cout << a[i] << endl ;
    }

    StaticArray<int,5> b ;

    b = a ;
    cout << " After b = a " << endl ;
    cout << " Read from StaticArray b :" << endl ;
    for ( int i = 0 ; i < b.length() ; i++ )
    {
        cout << b[i] << endl ;
    }

    // b[6] = 100 ; // 越界测试
}

void TestDynamicArray()
{
    DynamicArray<int> a(5);

    for ( int i = 0 ; i < a.length() ; i++ )
    {
        a[i] = i * i ;
    }
    cout << " Read from DynamicArray a :" << endl ;
    for ( int i = 0 ; i < a.length() ; i++ )
    {
        cout << a[i] << endl ;
    }

    DynamicArray<int> b(5) ;

    b = a ;

    b.resize(8);
    cout << " After b = a " << endl ;
    cout << " Read from DynamicArray b :" << endl ;
    for ( int i = 0 ; i < b.length() ; i++ )
    {
        cout << b[i] << endl ;
    }
}

void TestLinkList()
{
    LinkList<int> list;

    for( int i = 0 ; i < 5 ; i++ )
    {
        list.insert(i);
        list.set(i,i*i);
    }

    cout << "length: " << list.length() << endl ;
    for ( int i = 0 ; i < list.length() ; i++ )
    {        
        cout <<  list.get(i) << endl;
    }

    list.remove(2);
    cout << "length: " << list.length() << endl ;
    for ( int i = 0 ; i < list.length() ; i++ )
    {
        cout <<  list.get(i) << endl;
    }
}

class problem : public Object{
    int i ;
public :
    problem( int v = 0 )
    {
        i = v  ;
    }

    bool operator ==( const problem& obj)
    {
        return ( i == obj.i );
    }

};

void TestLinkListHeaderProblem()
{
    problem t1(1);
    problem t2(2);
    problem t3(3);
    LinkList<problem> list ;  // 不会发生问题
    list.insert(t1);
    list.insert(t2);
    list.insert(t3);

    cout << list.find(t2) << endl;
//    problem t ;
//    list.insert(t);
    cout << "Test LinkList problem!" << endl;
}

void TestLinklistFind()
{
    StaticLinkList<int,5> list ;

    for ( int i = 0 ; i < 5 ; i++){
        list.insert(0,i);
    }

    try
    {
        list.insert(6);
    }catch( const Exception& e)
    {
        cout << e.message()<< endl ;
    }

    // 这里的时间复杂度为:O(n)，采用了游标的设计思想
    for ( list.move(0) ; !list.end() ; list.next() ){
        cout << list.current() << endl;
    }
}

class Bug1 : public Object
{
    int m_id;
public:
    Bug1(int id = 0)
    {
        m_id = id;
    }

    ~Bug1()
    {
        if( m_id == 1 )
        {
            throw m_id;
        }
    }
};

void TestBugFix1()
{
    cout << "in bugfix 1" << endl;
    LinkList<Bug1> list;
    Bug1 t0(0), t1(1), t2(2);

    try
    {
        list.insert(t0);
        list.insert(t1);
        list.insert(t2);

        list.remove(1);
    }
    catch(int e)
    {
        cout << e << endl;
        cout << list.length() << endl;
    }
}

void TestBugFix2()
{
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(i);
    }

    for(list.move(0); !list.end(); list.next())
    {
        if( list.current() == 3 )
        {
            list.remove(list.find(list.current()));
        }
    }

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << endl;
    }
}



int main()
{
    //TestSmartPointer();
    //TestException();
    //TestObject();
    //TestDynamicList();
    //TestStaticArray();
    //TestDynamicArray();
    //TestLinkList();
    //TestLinkListHeaderProblem();
    //TestLinklistFind();
    //TestBugFix1();
    TestBugFix2();
    return 0;
}
