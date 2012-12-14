//
//  TradePost.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/14/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_TradePost_h
#define broc_TradePost_h

#include "Location.h"
#include <stdlib.h>

class TradePost
{
public:
    TradePost(const Location& loc = Location::SanFrancisco());
    ~TradePost();

    // Placement new operator
    inline void* operator new (size_t sz, void* object)
    {
        return object;
    }

    // properties
    inline void SetLoc(const Location& loc)
    {
        m_loc = loc;
    }
    inline Location GetLoc() const
    {
        return m_loc;
    }
    
protected:
    Location m_loc;
};

#endif
