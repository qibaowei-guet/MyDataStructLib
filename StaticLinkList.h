#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace MyDataStructLib {

template < typename T , int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node ; // typename用来表明Node是一个类，而不是一个成员

    struct SNode : public Node
    {
        void* operator new(unsigned int size , void* loc)
        {
            return loc; //loc保存了构造函数的内存地址
        }
    };

    unsigned char m_space[sizeof(SNode)*N] ;   // 自定义的内存空间
    int used[N]; // 内存标记

    Node* create()
    {
        SNode* ret = NULL;

        for ( int i = 0 ; i < N ; i++ ){
            if ( !used[i] )
            {
                // 分配内存
                ret = reinterpret_cast<SNode*>(m_space) + i ; // 指针的操作、运算
                ret = new(ret)SNode(); // 在刚刚分配的空间上面调用构造函数
                used[i]=1; // 标记
                break;
            }
        }
        return ret;
    }

    void destroy(Node *pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn   = dynamic_cast<SNode*>(pn);
        for ( int i = 0 ; i < N ; i++ )
        {
            if ( psn == (space + i) )
            {
                used[i] = 0 ;
                psn->~SNode();//调用析构函数
                break;
            }
        }
    }


public:
    StaticLinkList()
    {
        for (int i = 0 ; i < N ; i++ )
        {
            used[i] = 0 ;
        }
    }

    int capacity()
    {
        return N;
    }
};


};


#endif // STATICLINKLIST_H
