#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

/*
 * 智能指针要满足三个要求:
 * 1. 指针生命周期结束时，将对应的堆空间释放
 * 2. 不能两次释放同一片堆空间。
 * 3. 杜绝指针的运算和指针比较操作。
 *
 */

namespace MyDataStructLib {

    template < typename T >
    class SmartPointer : public Object
    {
    private:
        T* m_pointer;
    public:
        SmartPointer(T* p = NULL)
        {
            m_pointer = p ;
        }
        // 拷贝构造函数：一片堆空间只有一个指针指向，防止释放2次
        SmartPointer(const SmartPointer<T>& obj)
        {
            m_pointer = obj.m_pointer ;
            // obj.m_pointer = NULL ;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }
        // 重载赋值操作符
        SmartPointer<T>& operator=(const SmartPointer<T>& obj)
        {
            // 防止自赋值
            if ( this != &obj ){
                m_pointer = obj.m_pointer ;
                // obj.m_pointer = NULL ;
                const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            }
            return *this;
        }
        // 重载->和*操作符
        T* operator->()
        {
            return m_pointer;
        }
        T& operator*()
        {
            return *m_pointer;
        }

        bool isNull()
        {
            return ( m_pointer == NULL );
        }

        T* get()
        {
            return m_pointer;
        }

        ~SmartPointer()
        {
            delete m_pointer;
        }
    };


};

#endif // SMARTPOINTER_H
