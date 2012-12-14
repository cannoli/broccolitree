//
//  GameManager.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/8/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "GameManager.h"
#include "LocalMap.h"
#include "TradePostFactory.h"
#include "TradePostLocal.h"
#include "TouchRect.h"
#include "Camera.h"
#include "GLKMath.h"
#include <iostream>

// TODO: move mainCamera to LocalMap, and then no need to include this anymore
#include "GameRenderer.h"



using namespace std;

//
// singleton
//
GameManager* GameManager::singleton = NULL;

//
// constructor/destructor
//
GameManager::GameManager()
: m_localMap(NULL)
, m_curTradePost(0)
, m_tradePostLocals(NULL)
{
}

GameManager::~GameManager()
{
}

//
// game flow
//
void GameManager::StartGame()
{
    
}

void GameManager::FinishGame()
{
    
}

void GameManager::ScanTradePosts()
{
}

void GameManager::ClearTradePosts()
{
}

void GameManager::Update(double elapsed)
{
    if(m_localMap)
    {
        UpdateLocal(elapsed);
    }
}

//
// local map
// 
void GameManager::StartLocalGame()
{
    TradePostFactory::CreateInstance(50);

    m_localMap = new LocalMap;
    m_tradePostLocals = new list<TradePostLocal*>;
    ScanTradePostsLocal();
}

void GameManager::FinishLocalGame()
{
    ClearTradePostsLocal();
    delete m_tradePostLocals;
    delete m_localMap;
    
    TradePostFactory::DestroyInstance();
}
void GameManager::ScanTradePostsLocal()
{
    // query server for trade posts
    static float tradePos[9][3] = {
        {0.0f, 0.0f, 0.5f},
        {4.0f, 0.0f, 0.5f},
        {3.0f, 4.0f, 0.5f},
        {-2.0f, 0.0f, 0.5f},
        {-2.0f, 2.0f, 0.5f},
        {1.0f, -2.0f, 0.5f},
        {-10.0f, 4.0f, 0.5f},
        {10.0f, -7.0f, 0.5f},
        {5.0f, -3.0f, 0.5f}
    };
    static const char* names[9] = {
        "Homebase",
        "Downtown",
        "SOMA",
        "Castro",
        "Noe Valley",
        "Richmond",
        "Sunset",
        "Potrero",
        "Mission"
    };
    
    // retire old trade posts to reuse their space
    // TODO    
    
    // create new trade-posts
    for(unsigned int i = 0; i < 9; ++i)
    {
        TradePostLocal* chunk = TradePostFactory::GetInstance()->NewTradePostLocal();
        if(chunk)
        {
            TradePostLocal* newPost = new (chunk) TradePostLocal(tradePos[i][0], tradePos[i][1], tradePos[i][2]);
            newPost->SetName(names[i]);
            m_tradePostLocals->push_back(newPost);
            
            // inform active view of tradepost changes
            m_localMap->TradePostDidLoad(newPost);
        }
    }
}

void GameManager::ClearTradePostsLocal()
{
    for(list<TradePostLocal*>::iterator it = m_tradePostLocals->begin(); it != m_tradePostLocals->end(); it++)
    {
        // inform active view of deletion
        m_localMap->TradePostWillDelete(*it);
        
        // delete
        (*it)->~TradePostLocal();
        TradePostFactory::GetInstance()->RemoveTradePostLocal(*it);
    } 
    m_tradePostLocals->clear();
}

void GameManager::UpdateLocal(double elapsed)
{
    for(list<TradePostLocal*>::iterator it = m_tradePostLocals->begin(); it != m_tradePostLocals->end(); it++)
    {
        (*it)->RefreshTouchRect(GameRenderer::GetInstance()->GetMainCamera()->ViewProjectionMatrix());
    }    
}

TradePostLocal* GameManager::SelectTradePost(float screenX, float screenY)
{
    TradePostLocal* result = NULL;
    unsigned int count = 0;
    for(list<TradePostLocal*>::iterator it = m_tradePostLocals->begin(); it != m_tradePostLocals->end(); it++)
    {
        const TouchRect* rect = (*it)->GetTouchRect();
        if(rect->DoesContainPoint(screenX, screenY))
        {
            if(result)
            {
                // if there's an overlapping rect, pick the one with the smaller z
                if(rect->GetZDist() < result->GetTouchRect()->GetZDist())
                {
                    result = (*it);
                    //cout << "  Selected due to Z " << rect->GetZDist();
                }
                cout << endl;
            }
            else 
            {
                result = (*it);
                //cout << "Selected " << count << "  Z " << result->GetTouchRect()->GetZDist() << endl;
            }
        }
        ++count;
    }    
    
    if(result && m_localMap)
    {
        // if selected, focus on it in localmap
        m_localMap->FocusOnTradePost(result);
    }
    
    return result;
}

void GameManager::SelectNextTradePost()
{
    if(m_localMap)
    {
        unsigned int index = 0;
        TradePostLocal* selected = NULL;
        for(list<TradePostLocal*>::iterator it = m_tradePostLocals->begin(); it != m_tradePostLocals->end(); it++)
        {
            selected = *it;
            if(index >= m_curTradePost)
            {
                break;
            }
            ++index;
        }
        
        if(selected)
        {
            m_localMap->FocusOnTradePost(selected);
        }
        
        // increment next index
        m_curTradePost++;
        if(m_curTradePost >= m_tradePostLocals->size())
        {
            m_curTradePost = 0;
        }
    }
}