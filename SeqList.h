#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace MyDataStructLib {

template < typename T >
class SeqList : public List<T>
{
protected:
    int m_length;
    T*  m_array;
public:
    virtual int capacity() const = 0;
    bool get(int i, T &e) const
    {
        bool ret = ( ( i >= 0 )&& ( i <= m_length) );

        if ( ret ){
            e = m_array[i];
        }

        return ret ;
    }

    bool set(int i, const T& e)
    {
        bool ret = ( ( i >= 0 )&& ( i <= m_length) );

        if ( ret ){
            m_array[i] = e;
        }

        return ret ;
    }

    bool insert(int i, const T &e)
    {
        bool ret = ( ( i >= 0 )&& ( i <= m_length) );

        ret = ret && ( m_length  < capacity() );

        if ( ret ){

            for ( int p = m_length - 1 ; p >= i ; p++ ){
                m_array[p + 1 ] = m_array[p];
            }

            m_array[i] = e;
            m_length++;
        }

        return ret ;
    }

    bool remove(int i)
    {
        bool ret =  ( ( i >= 0 )&& ( i <= m_length) );

        if ( ret ) {

            for ( int p = i ; p < m_length - 1; p++ ){
                m_array[p] = m_array[p + 1] ;
            }
        }

        return ret ;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0 ;
    }

    T& operator[](int i )
    {
        if ( ( i >= 0 )&& ( i <= m_length) ){
            return m_array[i];
        }
        else {
            THROW_EXCEPTION(IndexOutOfBoundsException , "Paratmer i is invalid...");
        }
    }

    // ΪʲôҪ�ṩconst�汾
    T operator [](int i ) const
    {
        // �ֽ�: SeqList<T>&
        //      const_cast< >
        //                   (*this)
        //                          [i]
        return (const_cast<SeqList<T>&>(*this))[i];
    }
};

}

#endif // SEQLIST_H
