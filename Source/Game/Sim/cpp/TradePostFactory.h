//
//  TradePostFactory.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/9/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_TradePostFactory_h
#define broc_TradePostFactory_h

#include "FixedPool.h"

class TradePost;
class TradePostLocal;
class TradePostFactory
{
public:
    // mapview
    TradePost* NewTradePost();
    void RemoveTradePost(TradePost* toRemove);
    
    // localmap
    TradePostLocal* NewTradePostLocal();
    void RemoveTradePostLocal(TradePostLocal* toRemove);    
    
protected:
    FixedPool<TradePostLocal>* m_localPool;
    FixedPool<TradePost>* m_pool;

private:
    
// singleton
    static TradePostFactory* singleton;
    TradePostFactory(unsigned int poolsize = 50);    

public:
    static inline TradePostFactory* GetInstance()
    {
        if(!singleton)
        {
            singleton = new TradePostFactory;
        }
        return singleton;
    }
    static inline TradePostFactory* CreateInstance(unsigned int poolsize = 50)
    {
        if(!singleton)
        {
            singleton = new TradePostFactory(poolsize);
        }
        return GetInstance();
    }
    static inline void DestroyInstance()
    {
        if(singleton)
        {
            delete singleton;
        }
    }
    virtual ~TradePostFactory();
};

#endif
