#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

/*
 * ����ָ��Ҫ��������Ҫ��:
 * 1. ָ���������ڽ���ʱ������Ӧ�Ķѿռ��ͷ�
 * 2. ���������ͷ�ͬһƬ�ѿռ䡣
 * 3. �ž�ָ��������ָ��Ƚϲ�����
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
        // �������캯����һƬ�ѿռ�ֻ��һ��ָ��ָ�򣬷�ֹ�ͷ�2��
        SmartPointer(const SmartPointer<T>& obj)
        {
            m_pointer = obj.m_pointer ;
            // obj.m_pointer = NULL ;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }
        // ���ظ�ֵ������
        SmartPointer<T>& operator=(const SmartPointer<T>& obj)
        {
            // ��ֹ�Ը�ֵ
            if ( this != &obj ){
                m_pointer = obj.m_pointer ;
                // obj.m_pointer = NULL ;
                const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            }
            return *this;
        }
        // ����->��*������
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
