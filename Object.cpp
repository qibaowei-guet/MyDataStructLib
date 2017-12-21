#include "Object.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>


// ∂•≤„∏∏¿‡
using namespace std;

namespace MyDataStructLib {

void* Object::operator new(unsigned int size ) throw()
{
    void* ret = NULL ;

    cout << "Object::operator new size:" << size << endl;
    ret = malloc(size);

    return ret ;
}

void  Object::operator delete(void *p)
{
    cout << "Object::operator delete:" << p << endl;
    free(p);
}

void* Object::operator new[](unsigned int size ) throw()
{
    void* ret = NULL ;
    cout << "Object::operator new[] size:" << size << endl;
    ret = malloc(size);

    return ret ;
}

void  Object::operator delete[](void *p)
{
    free(p);
}

Object::~Object()
{

}



};
