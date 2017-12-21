#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"
#include <iostream>

using namespace std;

namespace MyDataStructLib {

template < typename T >
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if ( this->m_array != NULL ){
            this->m_length   = 0 ;
            this->m_capacity = capacity ;
        }else{
            THROW_EXCEPTION(NoEnoughMemoryException , "No Enough Memory For DynamicList");
        }
    }

    int capacity() const
    {
        return m_capacity ;
    }
    void resize( int capacity )
    {
        if ( capacity != m_capacity ){
            T* temp = new T[capacity];

            if ( temp != NULL ){

                int length = (this->m_length < capacity ? this->m_length : capacity);

                for( int i = 0 ; i < length ; i++ ){
                    temp[i] = this->m_array[i];
                }

                T* array = this->m_array ;

                this->m_array = temp ;
                this->m_length = length;
                this->m_capacity = capacity ;

                delete[] array;

            }else{
                THROW_EXCEPTION(NoEnoughMemoryException , "resize the capacity of DynamicList Error");
            }
        }

    }

    ~DynamicList()
    {
        //cout << "~DynamicList()" << endl;
        delete[] this->m_array;
    }
};

}


#endif // DYNAMICLIST_H
