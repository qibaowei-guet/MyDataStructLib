#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace MyDataStructLib {

//char *m_message;
//char *m_location;
void Exception::init(const char* message , const char* file , int line)
{
    m_message = ( message ? strdup(message) : NULL );

    if ( file != NULL ){
        char s[16] = { 0 };
        itoa(line , s , 10 );
        m_location  = static_cast<char*>(malloc(strlen(file) + strlen(s) + 2 )); //包括中间一个冒号和末尾一个结束符'\0'

        if ( m_location != NULL ){
            m_location  = strcpy(m_location , file);
            m_location  = strcat(m_location , ":" );
            m_location  = strcat(m_location , s );
        }

        // 这里没有else分支，注意这里不能抛出内存不足异常，因为这里是父类的init函数，逻辑上不通；从代码的运行上，抛出内存不足异常会造成死循环

    }else{
        m_location = NULL ;
    }
}

Exception::Exception(const char* message)
{
    init(message,NULL,0);
}

Exception::Exception(const char* file , int line)
{
    init(NULL,file,line);
}

Exception::Exception(const char* message , const char* file , int line)
{
    init(message,file,line);
}

Exception::Exception(const Exception& obj)
{
    m_message  = strdup(obj.m_message);
    m_location = strdup(obj.m_location);
}

Exception& Exception::operator=(const Exception& obj)
{
    if ( this != &obj){
        m_message  = strdup(obj.m_message);
        m_location = strdup(obj.m_location);
    }
    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

};
