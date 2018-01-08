#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace MyDataStructLib {

// 代码优化: 小、一个函数做一件事情
template < typename T >
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    void init(T* array , int len)
    {
        if ( array != NULL )
        {
            this->m_array  = array;
            this->m_length = len ;
        }else{
            THROW_EXCEPTION(NoEnoughMemoryException , " init DynamicArray error!...");
        }
    }

    T* copy(T* array , int len , int newLen)
    {
        T* ret = new T[newLen];

        if ( ret != NULL )
        {
            int minLen = ( newLen < len ) ? newLen : len ;
            for ( int i= 0 ; i < minLen ; i++ )
            {
                ret[i] = array[i];
            }
        }
        return ret ;
    }

    void update(T* array , int len)
    {
        if ( array != NULL )
        {
            // 异常安全
            T* temp = this->m_array ;

            this->m_array = array ;
            this->m_length = len ;

            delete[] temp;

        }else{
            THROW_EXCEPTION(NoEnoughMemoryException , " update DynamicArray error!...");
        }
    }

public:
    DynamicArray(int length)
    {
        init(new T[length] , length );
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        init(new T[obj.m_length] , obj.m_length );
        /////////////////////////////////////////////
        this->m_array = new T[obj.m_length];

        if ( this->m_array != NULL )
        {
            // 赋值
            for ( int i = 0 ; i < obj.m_length ; i++ )
            {
                this->m_array[i] = obj.m_array[i];
            }

            this->m_length = obj.m_length ;
        }else{
            THROW_EXCEPTION(NoEnoughMemoryException , " new DynamicArray(const DynamicArray<T>& obj) error!...");
        }
    }

    DynamicArray<T>& operator=( const DynamicArray<T>& obj)
    {
        if ( this != &obj )
        {
            this->m_array = new T[obj.m_length];

            if ( this->m_array != NULL )
            {
                // 赋值
                for ( int i = 0 ; i < obj.m_length ; i++ )
                {
                    this->m_array[i] = obj.m_array[i];
                }

                this->m_length = obj.m_length ;
            }else{
                THROW_EXCEPTION(NoEnoughMemoryException , " new DynamicArray operator= error!...");
            }
        }

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length )
    {
        if ( length != m_length ){


            ////////////////////////////////
            T* array = new T[length] ;

            if ( array != NULL ){

                int minLen = ( length < m_length ) ? length : m_length ;

                for ( int i = 0 ; i < minLen ; i++ )
                {
                    array[i] = this->m_array[i] ;
                }

                T* temp = this->m_array ;

                this->m_array  = array  ;
                this->m_length = length ;

                delete[] temp;
            }else{
                THROW_EXCEPTION(NoEnoughMemoryException , "resize DynamicArray length error!");
            }
        }

    }

    ~DynamicArray()
    {
        delete[] this->m_array ;
    }
};

}

#endif // DYNAMICARRAY_H
