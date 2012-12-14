//
//  GameManager.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/8/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_GameManager_h
#define broc_GameManager_h


#include <list>
#include "Location.h"

class LocalMap;
class TradePostLocal;
class GameManager
{
public:
    static inline GameManager* GetInstance()
    {
        if(!singleton)
        {
            singleton = new GameManager;
        }
        return singleton;
    }
    static inline GameManager* CreateInstance()
    {
        return GetInstance();
    }
    static inline void DestroyInstance()
    {
        if(singleton)
        {
            delete singleton;
        }
    }
    virtual ~GameManager();

    // game flow
    void StartGame();
    void FinishGame();
    void ScanTradePosts();
    void ClearTradePosts();
    void Update(double elapsed);
    
    Location GetTopFlyerLocation();
    
    // local map
    void StartLocalGame();
    void FinishLocalGame();
    TradePostLocal* SelectTradePost(float screenX, float screenY);
    void SelectNextTradePost();
    
protected:
    std::list<TradePostLocal*>* m_tradePostLocals;
    LocalMap* m_localMap;   
    unsigned int m_curTradePost;
    
    void UpdateLocal(double elapsed);
    void ScanTradePostsLocal();
    void ClearTradePostsLocal();
    
private:
    static GameManager* singleton;
    GameManager();    
};

#endif
