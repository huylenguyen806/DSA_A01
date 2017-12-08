/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class DSAException
{
    int _error;
    string _text;

  public:
    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char *text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string &getErrorText() { return _text; }
};

template <class T>
struct L1Item
{
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List
{
    L1Item<T> *_pHead; // The head pointer of linked list
    L1Item<T> *_pLast; // The last pointer of linked list
    size_t _size;      // number of elements in this list
  public:
    L1List() : _pHead(NULL), _pLast(NULL), _size(0) {}
    L1List(T &a) : _pHead(a), _pLast(a), _size(1) {}
    ~L1List()
    {
        destroy();
        _size = 0;
    }

    void destroy();

    bool isEmpty()
    {
        return _pHead == NULL;
    }
    size_t getSize()
    {
        return _size;
    }

    T &at(int i);
    T &operator[](int i);

    bool find(T &a, int &idx);
    int insert(int i, T &a);
    int insertTail(T &a);
    int remove(int i);

    int push_back(T &a);
    int insertHead(T &a);

    int removeHead();
    int removeLast();

    void reverse();

    T &getLast();

    L1Item<T> *&pointerHead()
    {
        return _pHead;
    }

    L1Item<T> *&pointerLast()
    {
        return _pLast;
    }

    bool traverse(bool (*op)(T, T, T, T), T n4)
    {
        L1Item<T> *p = _pHead;
        while (p->pNext != NULL)
        {
            if (op(p->data, p->pNext->data, _pLast->data, n4))
                return true;
            p = p->pNext;
        }
        return false;
    }

    bool traverse(bool (*op)(T &, T &), T &id)
    {
        L1Item<T> *p = _pHead;
        while (p != NULL)
        {
            if (op(p->data, id))
                return true;
            p = p->pNext;
        }
        return false;
    }

    void traverseGreater(bool (*op)(T &, T &), T &n)
    {
        L1Item<T> *p = _pHead;
        while (p != NULL)
        {
            if (op(p->data, n))
            {
                n = p->data;
            }
            p = p->pNext;
        }
    }

    void traverse(void (*op)(T &))
    {
        L1Item<T> *p = _pHead;
        while (p)
        {
            op(p->data);
            p = p->pNext;
        }
    }
    void traverse(void (*op)(T &, T &), T &a)
    {
        L1Item<T> *p = _pHead;
        while (p)
        {
            op(p->data, a);
            p = p->pNext;
        }
    }
    void traverse(void (*op)(T &, void *), void *pParam)
    {
        L1Item<T> *p = _pHead;
        while (p)
        {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
    void removeAll(T &a)
    {
        L1Item<T> *pre = _pHead;
        L1Item<T> *cur = _pHead->pNext;
        while (cur)
        {
            if (cur->data == a)
            {
                L1Item<T> *del = cur;
                pre->pNext = cur->pNext;
                delete del;
                cur = pre->pNext;
                _size--;
                continue;
            }
            pre = cur;
            cur = cur->pNext;
        }
        _pLast = pre;
        if (_pHead->data == a)
        {
            removeHead();
        }
    }

    void printList();
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a)
{
    if (_pHead == NULL)
    {
        _pHead = new L1Item<T>(a);
    }
    else
    {
        L1Item<T> *p = _pHead;
        while (p->pNext)
            p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a)
{
    L1Item<T> *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead()
{
    if (_pHead)
    {
        L1Item<T> *p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        if (_size == 0)
            _pLast = _pHead;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast()
{
    if (_pHead)
    {
        if (_pHead->pNext)
        {
            L1Item<T> *prev = _pHead;
            L1Item<T> *pcur = prev->pNext;
            while (pcur->pNext)
            {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
            _pLast = prev;
        }
        else
        {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}

///////////////======================Self-define======================////////////////

/// Reverse the list
template <class T>
void L1List<T>::reverse()
{
    L1Item<T> *temp = new L1Item<T>();
    while (_pHead != NULL)
    {
        temp->data = _pHead->data;
        L1Item<T> *t = new L1Item<T>();
        t->pNext = temp;
        temp = t;
        _pHead = _pHead->pNext;
    }
    _pHead = temp->pNext;
    delete temp;
}

/// Remove the ith item of the list
/// Return 0 if success, else return -1
template <class T>
int L1List<T>::remove(int i)
{
    if (i == 0)
    {
        removeHead();
        return 0;
    }
    else if (i == _size - 1)
    {
        removeLast();
        return 0;
    }
    else if (i > 0 & i < _size - 1)
    {
        L1Item<T> *pre = _pHead;
        L1Item<T> *curr = _pHead;
        while (i != 0)
        {
            pre = curr;
            curr = curr->pNext;
            i--;
        }
        pre->pNext = curr->pNext;
        delete curr;
        return 0;
    }
    else
    {
        return -1;
    }
}

/// Insert an item into the list
/// Return 0 if success
template <class T>
int L1List<T>::insert(int i, T &a)
{
    if (i == 0)
    {
        insertHead(a);
        return 0;
    }
    if (i > 0 && i < _size)
    { //from 1 to size - 1
        L1Item<T> *pre = _pHead;
        L1Item<T> *curr = _pHead;
        while (i != 0)
        {
            pre = curr;
            curr = curr->pNext;
            i--;
        }
        pre->pNext = new L1Item<T>(a);
        pre->pNext->pNext = curr;
        _size++;
        return 0;
    }
    else if (i == _size)
    {
        insertTail(a);
        return 0;
    }
    else
    {
        return -1;
    }
}

/// Insert an item into the tail of linked list
/// Return 0 if success
template <class T>
int L1List<T>::insertTail(T &a)
{
    if (_pLast == NULL)
    {
        insertHead(a);
        _pLast = _pHead;
        return 0;
    }
    _pLast->pNext = new L1Item<T>(a);
    _pLast = _pLast->pNext;
    _size++;
    return 0;
}

/// Find the item a
/// Get the index if found
template <class T>
bool L1List<T>::find(T &a, int &idx)
{
    L1Item<T> *temp = _pHead;
    idx = 0;
    while (temp != NULL)
    {
        if (a == temp->data)
        {
            return true;
        }
        temp = temp->pNext;
        idx++;
    }
    return false;
}

/// Operator[]
template <class T>
T &L1List<T>::operator[](int i)
{
    if (i <= _size - 1 && i >= 0)
    {
        L1Item<T> *temp = _pHead;
        while (i != 0)
        {
            temp = temp->pNext;
            i--;
        }
        T &ans = temp->data;
        return ans;
    }
}

/// At
/// if out-of-range then throw the exception
template <class T>
T &L1List<T>::at(int i)
{
    if (i <= _size - 1 && i >= 0)
    {
        operator[](i);
    }
}

/// Destroy the list
template <class T>
void L1List<T>::destroy()
{
    if (_pHead == NULL)
        return;
    while (_pHead != NULL)
    {
        L1Item<T> *del = _pHead;
        _pHead = _pHead->pNext;
        delete del;
    }
    _pLast = _pHead;
}

/// Print the list in the console
template <class T>
void L1List<T>::printList()
{
    L1Item<T> *t = _pHead;
    while (t != NULL)
    {
        if (t->pNext == NULL)
            cout << t->data << endl;
        else
            cout << t->data << " ";
        t = t->pNext;
    }
    delete t;
}

/// Get the last node
template <class T>
T &L1List<T>::getLast()
{
    T &ans = _pLast->data;
    return ans;
}

class NinjaData
{
  public:
    char id[10];
    bool first_code9 = false;
    bool first_code10 = false;
    bool first_code12 = false;
    bool first_code14 = false;
    double moving_distance = 0;
    double moving_time = 0;
    double stopping_time = 0;
    bool IsLost = false;
    NinjaData(char *_id)
    {
        strcpy(id, _id);
    }
    friend bool operator==(NinjaData &n1, NinjaData &n2)
    {
        return strcmp(n1.id, n2.id) == 0;
    }
    friend bool operator!=(NinjaData &n1, NinjaData &n2)
    {
        return strcmp(n1.id, n2.id) != 0;
    }
    friend bool operator>(NinjaData &n1, NinjaData &n2)
    {
        return strcmp(n1.id, n2.id) > 0;
    }
    friend bool operator<(NinjaData &n1, NinjaData &n2)
    {
        return strcmp(n1.id, n2.id) < 0;
    }
    void operator=(NinjaData &n)
    {
        strcpy(this->id, n.id);
        this->moving_distance = n.moving_distance;
        this->moving_time = n.moving_time;
        this->IsLost = n.IsLost;
        this->stopping_time = n.stopping_time;
    }
};
class Ninjas
{
  public:
    L1List<NinjaData> data;
    ~Ninjas()
    {
        data.destroy();
    }
    void insert(char *&_id)
    {
        NinjaData t(_id);
        if (!data.traverse(Equal, t))
        {
            data.insertTail(t);
        }
    }
    void remove(char *&_id)
    {
        NinjaData t(_id);
        data.removeAll(t);
    }
    static bool Equal(NinjaData &n1, NinjaData &n2)
    {
        return n1 == n2;
    }
};

class GData {
    public:
        Ninjas *ninjas;
        string FirstID, LastID;
        string eve;
        bool _code9;
        bool _code10;
        bool _code12;
        bool _code14;
        bool init;
        GData(){
            ninjas = new Ninjas();
            eve = "";
            FirstID = "";
            LastID = "";
            _code9 = false;
            _code10 = false;
            _code12 = false;
            _code14 = false;
            init = false;
        }
        ~GData(){
            delete ninjas;
            eve.clear();
            FirstID.clear();
            LastID.clear();
        }
};
#endif //A01_LISTLIB_H
