#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace MyDataStructLib {

template < typename T >
class DynamicArray : public Array<T>
{
protected:
    int m_length;
public:
    DynamicArray(int length)
    {
        this->m_array = new T[length];

        if ( this->m_array != NULL )
        {
            this->m_length = length;
        }else{
            THROW_EXCEPTION(NoEnoughMemoryException , " new DynamicArray error!...");
        }
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        this->m_array = new T[obj.m_length];

        if ( this->m_array != NULL )
        {
            // ¸³Öµ
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
                // ¸³Öµ
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

    }

    ~DynamicArray()
    {
        delete[] this->m_array ;
    }
};

}

#endif // DYNAMICARRAY_H
