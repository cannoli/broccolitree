//
//  LocalMap.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_LocalMap_h
#define broc_LocalMap_h

class CubeShape;
class TradePostLocal;
class GroundPlane;
class LocalMap
{
public:
    LocalMap();
    ~LocalMap();
    
    // callback from GameManager when TradePosts are refreshed
    void TradePostDidLoad(TradePostLocal* tradePost);
    void TradePostWillDelete(TradePostLocal* tradePost);
    
    // controls
    void FocusOnTradePost(TradePostLocal* tradePost);
    
protected:
    // components
    GroundPlane* m_groundPlane;

private:
};

#endif
