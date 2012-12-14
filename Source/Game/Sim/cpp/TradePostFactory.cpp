//
//  TradePostFactory.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/9/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "TradePostFactory.h"
#include "TradePostLocal.h"
#include "TradePost.h"
#include <iostream>
#include <assert.h>


//
// singleton
//
TradePostFactory* TradePostFactory::singleton = NULL;

//
// constructor/destructor
//
TradePostFactory::TradePostFactory(unsigned int poolsize)
{
    m_localPool = new FixedPool<TradePostLocal>(poolsize);
    m_pool = new FixedPool<TradePost>(poolsize);
}

TradePostFactory::~TradePostFactory()
{
    delete m_pool;
    delete m_localPool;
}


//
// allocation routines
//
// 2d mapview
TradePost * TradePostFactory::NewTradePost()
{
    TradePost* chunk = m_pool->Alloc();
    TradePost* newPost = new (chunk) TradePost;
    
    return newPost;    
}
void TradePostFactory::RemoveTradePost(TradePost *toRemove)
{
    toRemove->~TradePost();
    m_pool->Free(toRemove);
}


// localmap
TradePostLocal* TradePostFactory::NewTradePostLocal()
{
    TradePostLocal* chunk = m_localPool->Alloc();
    TradePostLocal* newPost = new (chunk) TradePostLocal;
    
    return newPost;
}

void TradePostFactory::RemoveTradePostLocal(TradePostLocal *toRemove)
{
    toRemove->~TradePostLocal();
    m_localPool->Free(toRemove);
}
