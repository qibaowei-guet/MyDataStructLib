#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace MyDataStructLib {

#define THROW_EXCEPTION(e,m) ( throw e(m , __FILE__ , __LINE__ ))

class Exception : public Object
{
private:
    char *m_message;
    char *m_location;
    void init(const char* message , const char* file , int line);
public:
    Exception(const char* message);
    Exception(const char* file , int line);
    Exception(const char* message , const char* file , int line);

    Exception(const Exception& obj);
    Exception& operator=(const Exception& obj);

    virtual const char* message() const ;  // 前面的virtual表示，在使用的过程中会继承。
    virtual const char* location() const ; // 后面的const表示const成员函数，在函数里面不能对成员变量赋值修改。

    virtual ~Exception()  ; // 注意这里的=0
};

// 计算异常类
class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(0){} ;
    ArithmeticException(const char* message) : Exception(message){} ; // 注意后面的{}要写
    ArithmeticException(const char* file , int line) : Exception(file , line){} ;
    ArithmeticException(const char* message , const char* file , int line) : Exception(message , file ,line){} ;

    ArithmeticException(const ArithmeticException& obj) : Exception(obj){} ;

    ArithmeticException& operator=(const ArithmeticException& obj) {
        Exception::operator=(obj);
        return *this;
    }
};

// 空指针异常
class NullPointerException : public Exception
{
public:
    NullPointerException() : Exception(0){} ;
    NullPointerException(const char* message) : Exception(message){} ; // 注意后面的{}要写
    NullPointerException(const char* file , int line) : Exception(file , line){} ;
    NullPointerException(const char* message , const char* file , int line) : Exception(message , file ,line){} ;

    NullPointerException(const NullPointerException& obj) : Exception(obj){} ;

    NullPointerException& operator=(const NullPointerException& obj) {
        Exception::operator=(obj);
        return *this;
    }
};

// 越界异常
class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() : Exception(0){} ;
    IndexOutOfBoundsException(const char* message) : Exception(message){} ; // 注意后面的{}要写
    IndexOutOfBoundsException(const char* file , int line) : Exception(file , line){} ;
    IndexOutOfBoundsException(const char* message , const char* file , int line) : Exception(message , file ,line){} ;

    IndexOutOfBoundsException(const IndexOutOfBoundsException& obj) : Exception(obj){} ;

    IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& obj) {
        Exception::operator=(obj);
        return *this;
    }
};

// 内存不足异常
class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() : Exception(0){} ;
    NoEnoughMemoryException(const char* message) : Exception(message){} ; // 注意后面的{}要写
    NoEnoughMemoryException(const char* file , int line) : Exception(file , line){} ;
    NoEnoughMemoryException(const char* message , const char* file , int line) : Exception(message , file ,line){} ;

    NoEnoughMemoryException(const NoEnoughMemoryException& obj) : Exception(obj){} ;

    NoEnoughMemoryException& operator=(const NoEnoughMemoryException& obj) {
        Exception::operator=(obj);
        return *this;
    }
};

// 参数错误异常
class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() : Exception(0){} ;
    InvalidParameterException(const char* message) : Exception(message){} ; // 注意后面的{}要写
    InvalidParameterException(const char* file , int line) : Exception(file , line){} ;
    InvalidParameterException(const char* message , const char* file , int line) : Exception(message , file ,line){} ;

    InvalidParameterException(const InvalidParameterException& obj) : Exception(obj){} ;

    InvalidParameterException& operator=(const InvalidParameterException& obj) {
        Exception::operator=(obj);
        return *this;
    }
};

// 非法操作异常
class InvalidOperationException : public Exception
{
public:
    InvalidOperationException() : Exception(0){} ;
    InvalidOperationException(const char* message) : Exception(message){} ; // 注意后面的{}要写
    InvalidOperationException(const char* file , int line) : Exception(file , line){} ;
    InvalidOperationException(const char* message , const char* file , int line) : Exception(message , file ,line){} ;

    InvalidOperationException(const InvalidOperationException& obj) : Exception(obj){} ;

    InvalidOperationException& operator=(const InvalidOperationException& obj) {
        Exception::operator=(obj);
        return *this;
    }
};

}

#endif // EXCEPTION_H
