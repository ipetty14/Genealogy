//
//  list.h
//  doubly linked list
//
//  Created by Spencer Peck on 10/24/16.
//  Copyright © 2016 Spencer Peck. All rights reserved.
//

#ifndef LIST_H
#define LIST_H
#include "node.h"
template <class T>
class ListIterator;

template <class T>
class List
{
    
private:
    Node<T> * head;
    Node<T> * tail;
    int numItems;
public:
    List() : head(NULL), tail(NULL), numItems(0) {}
    // copy constructor
    List(const List <T> & rhs);
    //destructor
    ~List()        { if (numItems) freeData(head); tail = NULL;}
    
    // is the List currently empty
    bool empty() const  { return numItems == 0;         }
    
    // remove all the items from the List
    void clear()        { numItems = 0; freeData(head); tail = NULL;                }
    
    // how many items are currently in the List?
    int size() const    { return numItems;              }
    
    // add item to end of List and doubles if not enough space
    void push_back(const T & t) throw (const char *);
    
    // add item to end of List and doubles if not enough space
    void push_front(const T & t) throw (const char *);
    
    //return item in front
    T & front() throw (const char *);
    
    //return item in back
    T & back() throw (const char *);
    
    void insert(ListIterator<T> & it, T data) throw (const char *);
    
    void remove(ListIterator<T> & it) throw (const char *);
    


    
    //assignment = operator
    List <T> & operator = (const List<T> & rhs) throw (const char *)
    {
        try
        {
            freeData(head);
            //head = rhs.head;
            tail = rhs.tail;
            
            head = copy(rhs.head);
        }
        
        catch (std::bad_alloc)
        {
            throw "ERROR: unable to allocate a new node for a list";
        }
        
        return *this;
    }
    
    ListIterator<T> begin() const { return ListIterator<T>(head); }
    ListIterator<T> end() const { return ListIterator<T>(NULL); }
    ListIterator<T> rbegin() const { return ListIterator<T>(tail); }
    ListIterator<T> rend() const { return ListIterator<T>(NULL); }
    
    
    
};
    
/******************************
 *copy constructor:
 ******************************/
template <class T>
List <T> :: List(const List <T> & rhs)
{
    numItems = rhs.numItems;
    // set all the pointers and create first
    Node<T> * first = new Node<T>;
    Node<T> * temp = rhs.head;
    Node<T> * current = first;
        
    first->data = rhs.head->data;
        
    // loop through and set all pointers
    while (temp->pNext)
    {
        current->pNext = new Node<T>;
        current->pNext->pPrev = current;
        current = current->pNext;
        temp = temp->pNext;
        current->data = temp->data;
    }
    // set head and tail
    head = first;
    tail = current;
}

/******************************
 *Push Back
 ******************************/
template <class T>
void List <T> :: push_back(const T & t) throw (const char *)
{
   try
    {
        Node<T> * temp = new Node<T>(t);
        
        if (numItems == 0)
        {
            head = temp;
            tail = temp;
            numItems++;
        }
        else
        {
            tail->pNext = temp;
            temp->pPrev = tail;
            tail = temp;
            numItems++;
        }
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/******************************
 *Push Front
 ******************************/
template <class T>
void List <T> :: push_front(const T & t) throw (const char *)
{
    try
    {
        Node<T> * temp = new Node<T>(t);
        if (numItems == 0)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            temp->pNext = head;
            temp->pPrev = NULL;
            head->pPrev = temp;
            head = temp;
        }
        numItems++;
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/***************************************************
 * front :: return item in front
 *
 **************************************************/
template <class T>
T & List <T> :: front() throw (const char *)
{
    if (numItems <= 0)
        throw "ERROR: unable to access data from an empty list";
    
    return head->data;
    
}

/***************************************************
 * back :: return item in back
 *
 **************************************************/
template <class T>
T & List <T> :: back() throw (const char *)
{
    if (numItems <= 0)
        throw "ERROR: unable to access data from an empty list";
    
    return tail->data;
   
    
}

/***************************************************
 * Insert
 *
 **************************************************/
template<class T>
void List<T>::insert(ListIterator<T> & it, T data) throw(const char *)
{
    Node<T> * temp = new Node<T> (data);
    if (empty())
    {
        head = temp;
        tail = temp;
        temp->pPrev = NULL;
        temp->pNext = NULL;
        numItems++;
    }
    
    else if (it.p == head)
    {
        temp->pNext = head;
        temp->pPrev = NULL;
        head->pPrev = temp;
        head = temp;
        numItems++;
    }
    
    else if (it == end())
    {
        tail->pNext = temp;
        temp->pPrev = tail;
        tail = temp;
        numItems++;
    }
    
    else
    {
        temp->pNext = it.p;
        temp->pPrev = it.p->pPrev;
        it.p->pPrev = temp;
        temp->pPrev->pNext = temp;
        numItems++;
    }
   
}
/***************************************************
 * Remove
 **************************************************/
template<class T>
void List<T>::remove(ListIterator<T> & it) throw(const char *)
{
    if (it != end())
    {
        if (it.p == tail)
        {
            tail = tail->pPrev;
            tail->pNext = NULL;
        }
        
        else if (it.p == head)
        {
            head = head->pNext;
            head->pPrev = NULL;
        }
        
        else
        {
            it.p->pNext->pPrev = it.p->pPrev;
            it.p->pPrev->pNext = it.p->pNext;
        }
        
        delete it.p;
        it.p = NULL;
        
        numItems--;
    }
    
    else 
    {
        throw "ERROR: unable to remove from an invalid location in a list";
    }
    
    
}


/***************************************************
 * List iterator
 *
 **************************************************/
template <class T>
class ListIterator
{
public:

//Default Constructor
ListIterator() : p(NULL) {}

//Initialize to direct p to an item
ListIterator(Node<T> * p) : p(p) {}

//Copy Constructor
ListIterator(const ListIterator & rhs) { *this = rhs; }

//Assignment Operator
ListIterator & operator = (const ListIterator & rhs)
{
    this->p = rhs.p;
    return *this;
}

//Not Equals Operator
bool operator != (const ListIterator & rhs) const
{
    return rhs.p != this->p;
}

bool operator = (const ListIterator & rhs) const
{
    return rhs.p = this->p;
}

bool operator == (const ListIterator & rhs) const
{
    return rhs.p == this->p;
}

//Dereference Operator
T & operator * ()
{
    return p->data;
}

//Prefix Increment
ListIterator <T> & operator ++ ()
{
    p = p->pNext;
    return *this;
}

ListIterator <T> & operator -- ()
{
    p = p->pPrev;
    return *this;
}

//Postfix Increment
ListIterator <T> operator++(int postfix)
{
    ListIterator tmp(*this);
    p = p->pNext;
    return tmp;
}

ListIterator <T> operator--(int postfix)
{
    ListIterator tmp(*this);
    p = p->pPrev;
    return tmp;
}
    
Node<T> * p;
};




#endif /* list_h */
