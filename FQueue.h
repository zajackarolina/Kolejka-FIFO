#pragma once

#include <iostream>
using namespace std;

#define FIFO_ALLOCATION_ERROR  0x01
#define FIFO_QUEUE_EMPTY 0x04
#define OTHER_ERROR      0x10

/////////////////////////////////////////////////////////////////
class FifoException {
public:
    FifoException( int errCode = OTHER_ERROR );
    const char* getReason();
private:
    int m_errCode;

};
//inline
inline FifoException::FifoException( int errCode ) {
    m_errCode = errCode;
}

inline const char* FifoException::getReason() { //pobiera powod kodu bledu i zwraca napis zalezny od bledu
    switch (m_errCode)
    {
        case FIFO_ALLOCATION_ERROR:	 return "ERROR: ALLOCATION ERROR!";
        case FIFO_QUEUE_EMPTY:	 return "ERROR: FQUEUE IS EMPTY!";
        case OTHER_ERROR:	     return "ERROR: OTHER ERROR!";
        default:		 return "ERROR: UNKNOWN ERROR";
    }
}

template <class T>
class FifoItem {
private:
    FifoItem( T* pInfo ); // Konstruktor z parametrem info
    virtual ~FifoItem(); // Wirtualny destruktor

private:
    T* m_pItem; // Wskaźnik na element
    FifoItem<T>* m_pNext; // Wskaźnik na następny element

    template <typename T>
    friend class FQueue;
};

template <class T>
inline FifoItem<T>::FifoItem( T* pInfo ) {
    this->m_pItem = pInfo;
    this->m_pNext = nullptr;
}

template <class T>
inline FifoItem<T>::~FifoItem() 
{
}

template <class T>
class FQueue {
public:
    virtual ~FQueue(); // Wirtualny destruktor
    FQueue(); // Konstruktor bez parametrów

    bool FQEmpty();
    int FQEnqueue( T* r );
    T* FQDequeue();
    void FQClear();
    void printQUEUE();

private:
    void FQDel();
    FifoItem<T>* m_pHead;
    FifoItem<T>* m_pTail;
};

template <class T>
inline FQueue<T>::FQueue() {
    m_pHead = m_pTail = nullptr;
}

template <class T>
inline FQueue<T>::~FQueue() {
    while (!FQEmpty())
        FQDel();
}

template <class T>
bool FQueue<T>::FQEmpty() {
    return !m_pHead;
}

template <class T>
int FQueue<T>::FQEnqueue( T* pInfo ) {
    FifoItem<T>* pItem = new(nothrow) FifoItem<T>( pInfo );
    if (!pItem) {
        throw FifoException( FIFO_ALLOCATION_ERROR );
    }

    return m_pTail ? (m_pTail = m_pTail->m_pNext = pItem, 0) : (m_pTail = m_pHead = pItem, 0);
}

template <class T>
T* FQueue<T>::FQDequeue() {
    if (FQEmpty()) {
        throw FifoException( FIFO_QUEUE_EMPTY );
    }
    T* pRes = m_pHead->m_pItem;
    FQDel(); // Usuwa głowę kolejki
    return pRes;
}

template <class T>
void FQueue<T>::FQClear() {
    while (!FQEmpty()) {
        FQDel();
    }
}

template <class T>
void FQueue<T>::FQDel() {
    if (FQEmpty()) {
        return;
    }
    FifoItem<T>* pItem = m_pHead;
    m_pHead = m_pHead->m_pNext;
    delete pItem;
}

template <class T>
void FQueue<T>::printQUEUE() {
    FifoItem<T>* p = this->m_pHead;
    while (p) {
        cout << *(p->m_pItem) << endl;
        p = p->m_pNext;
    }
}
