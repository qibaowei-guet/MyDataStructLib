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
        m_location  = static_cast<char*>(malloc(strlen(file) + strlen(s) + 2 )); //�����м�һ��ð�ź�ĩβһ��������'\0'

        if ( m_location != NULL ){
            m_location  = strcpy(m_location , file);
            m_location  = strcat(m_location , ":" );
            m_location  = strcat(m_location , s );
        }

        // ����û��else��֧��ע�����ﲻ���׳��ڴ治���쳣����Ϊ�����Ǹ����init�������߼��ϲ�ͨ���Ӵ���������ϣ��׳��ڴ治���쳣�������ѭ��

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
