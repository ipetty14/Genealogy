//
//  node.h
//  linkedList
//
//  Created by Ian Petty on 10/19/16.
//  Copyright © 2016 Ian Petty. All rights reserved.
//

#ifndef node_h
#define node_h

#include <stdio.h>
#include <iostream>

using namespace std;

struct Family
{
    int father;
    int mother;
    int child;
};

struct Person
{
    string givenName;
    string lastName;
    string birthday;
    string birthYear;
    int id;
};

template <class T>
class Node
{
public:
    T data;
    Node * pNext;
    Node * pPrev;
    Node * pMother;
    Node * pFather;
    
    Node () : pNext(NULL), pPrev(NULL), pMother(NULL), pFather(NULL) {}
    Node(T data) : data(data), pNext(NULL), pPrev(NULL), pMother(NULL), pFather(NULL) {}
    
    void levelDisplay();
};

template <class T>
Node<T> * copy(Node<T>* rhs)
{
    Node<T> * pFirst = new Node<T>;
    Node<T> * pTemp = rhs;
    Node<T> * pCurrent = pFirst;
    
    pFirst->data = rhs->data;
    
    while (pTemp->pNext)
    {
        pCurrent->pNext = new Node<T>;
        pCurrent = pCurrent->pNext;
        pTemp = pTemp->pNext;
        pCurrent->data = pTemp->data;
    }
    
    return pFirst;
}

template <class T>
void insert (T data, Node<T> * & pNode, bool isHead = false)
{
    if (pNode == NULL)
    {
        Node<T> * temp = new Node<T> (data);
        pNode = temp;
    }
    else if (isHead == false)
    {
        Node<T> * pNew = new Node<T> (data);
        pNew->pNext = pNode->pNext;
        pNode->pNext = pNew;
    }
    else
    {
        Node<T> * pNew = new Node<T> (data);
        pNew->pNext = pNode;
        pNode = pNew;
    }
}

template <class T>
Node<T> * find (Node<T> * pHead, const T & data)
{
    Node<T> * pCurrent = pHead;
    
    while(pCurrent)
    {
        if(pCurrent->data == data)
        {
            return pCurrent;
        }
        
        pCurrent = pCurrent->pNext;
    }
    
    pCurrent = NULL;
    
    return pCurrent;
}


template <class T>
ostream & operator << (ostream & out, const Node<T> * pNode)
{
    for(const Node<T> * p = pNode; p; p = p->pNext)
    {
        if (p->pNext != NULL)
            out << p->data << ", ";
        else
            out << p->data;
    }
    
    return out;
}

template <class T>
void freeData(Node<T>* & pNode)
{
    Node<T> * temp = pNode;
    
    while (pNode != NULL)
    {
        temp = pNode->pNext;
        delete pNode;
        
        pNode = temp;
    }
    
    pNode = NULL;
}


#endif /* node_h */

