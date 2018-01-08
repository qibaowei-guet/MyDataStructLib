#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace MyDataStructLib{

template < typename T >
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value ;
        Node* next ;
    };

    mutable struct: public Object  // 保证和T的内存布局一致
    {
        char reserve[sizeof(T)];   // 这里只是保留了T的空间，而不构造T
        Node* next;
    }m_header;

    Node* m_current;  //游标
    int  m_step;      //游标步进
    int  m_length;

    Node* postion(int i) const
    {
        Node* current = reinterpret_cast<Node*>(&m_header) ;

        for ( int p = 0 ; p < i ; p++ ){
            current = current->next;
        }

        return current;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    LinkList()
    {
        m_current = NULL;
        m_header.next = NULL;
        m_step = 1 ; //默认为1个单位移动
        m_length = 0 ;
    }

    bool insert( const T& e)
    {
        return insert(m_length,e);
    }

    bool insert(int i , const T& e)
    {
        bool ret = ( ( i >= 0 ) && ( i <= m_length ) ) ;
        if ( ret ){

            Node* obj = create();

            if ( obj != NULL ){

                Node* current = postion(i);

                obj->value = e ;
                obj->next = current->next ;
                current->next = obj;

                m_length++ ;

            }else{
                THROW_EXCEPTION(NoEnoughMemoryException , "No memory for new node element");
            }
        }

        return ret ;
    }

    bool remove(int i )
    {
        bool ret = ( ( i >= 0 ) && ( i < m_length ) ) ;
        if ( ret ){
            Node* current = postion(i);
            Node* toDel = current->next;
            if ( m_current == toDel )
            {
                m_current = toDel->next; // 保证异常安全
            }
            current->next = toDel->next;
            m_length--; // 保证函数异常安全
            destroy(toDel);
        }
        return ret ;
    }

    T get(int i) const
    {
        T ret ;
        if ( get(i,ret))
        {
            return ret;
        }else{
            THROW_EXCEPTION(IndexOutOfBoundsException,"Invalid paramter i to get a element...");
        }
    }

    bool get(int i , T& e) const
    {
        bool ret = ( ( i >= 0 ) && ( i < m_length ) ) ;
        if ( ret ){
            e = postion(i)->next->value ;
        }
        return ret ;
    }

    bool set(int i , const T& e)
    {
        bool ret = ( ( i >= 0 ) && ( i < m_length ) ) ;
        if ( ret ){
            postion(i)->next->value = e ;
        }
        return ret ;
    }

    int  length() const
    {
        return m_length;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0 ;
        Node* node = m_header.next;

        while ( node ){
            if ( node->value == e ){
                ret = i ;
                break;
            }else {
                node = node->next;
                i++;
            }
        }
        return ret ;
    }

    bool move( int i , int step = 1)
    {
        bool ret = ( ( i >= 0 ) && ( i < m_length ) && ( step > 0 ) );

        if ( ret ){
            m_current = postion(i)->next;
            m_step = step;
        }

        return ret ;
    }

    bool end()
    {
        return ( m_current == NULL);
    }

    T current()
    {
        if ( !end()){
            return m_current->value;
        }else {
            THROW_EXCEPTION(InvalidParameterException,"No value at current postion...");
        }

    }

    bool next()
    {
        int i = 0 ;
        while( (i < m_step ) && (!end())){
            m_current = m_current->next;
            i++;
        }

        return ( i == m_step );
    }

    void clear()
    {
        while ( m_header.next ){
            Node* toDel = m_header.next;
            m_header.next = toDel->next;
            m_length--;
            destroy(toDel);
        }

    }

    ~LinkList()
    {
        clear();
    }

};

};



#endif // LINKLIST_H
