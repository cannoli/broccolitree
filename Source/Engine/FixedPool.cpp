//
//  FixedPool.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "FixedPool.h"
#include <iostream>
#include <assert.h>
#if 0
//
// construct/destructor
//
template <class T> FixedPool<T>::FixedPool(unsigned int poolSize)
: m_poolSize(poolSize)
{
    // this class assumes each chunk to have at least the size of a pointer because
    // it reuses empty chunks to store the next pointer
    assert(sizeof(T*) <= sizeof(T));
    
    m_pool = new T[poolSize];
    memset(m_pool, 0, sizeof(T) * poolSize);
    
    // init free list
    unsigned int index = 0;
    m_freeList = reinterpret_cast<Entry*>(&(m_pool[index]));
    while((index+1) < poolSize)
    {
        T* cur = &(m_pool[index]);
        T* next = &(m_pool[index+1]);
        
        Entry* curEntry = reinterpret_cast<Entry*>(cur);
        curEntry->next = reinterpret_cast<Entry*>(next);
        ++index;
    }
    Entry* lastEntry = reinterpret_cast<Entry*>(&(m_pool[poolSize-1]));
    lastEntry->next = NULL;
}

template <class T> FixedPool<T>::~FixedPool()
{
    // delete the pool
    delete [] m_pool;
}

//
// alloc/free
//
template <class T> T* FixedPool<T>::Alloc()
{
    // out of memory if m_freeList is NULL
    assert(m_freeList);
    
    T* result = reinterpret_cast<T*>(m_freeList);
    if(m_freeList)
    {
        m_freeList = m_freeList->next;
    }
    return result;
}

template <class T>
void FixedPool<T>::Free(T* chunk) 
{
    Entry* newFree = reinterpret_cast<Entry*>(chunk);
    newFree = m_freeList;
    m_freeList = newFree;
}

#endif
