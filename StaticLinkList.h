#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace MyDataStructLib {

template < typename T , int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node ; // typename��������Node��һ���࣬������һ����Ա

    struct SNode : public Node
    {
        void* operator new(unsigned int size , void* loc)
        {
            return loc; //loc�����˹��캯�����ڴ��ַ
        }
    };

    unsigned char m_space[sizeof(SNode)*N] ;   // �Զ�����ڴ�ռ�
    int used[N]; // �ڴ���

    Node* create()
    {
        SNode* ret = NULL;

        for ( int i = 0 ; i < N ; i++ ){
            if ( !used[i] )
            {
                // �����ڴ�
                ret = reinterpret_cast<SNode*>(m_space) + i ; // ָ��Ĳ���������
                ret = new(ret)SNode(); // �ڸոշ���Ŀռ�������ù��캯��
                used[i]=1; // ���
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
                psn->~SNode();//������������
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
