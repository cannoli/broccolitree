//
//  LocalMap.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "LocalMap.h"
#include "TradePostLocal.h"
#include "GroundPlane.h"
#include "GameRenderer.h"
#include "Camera.h"
#include <iostream>
#include <assert.h>

using namespace std;

//
// constructor/destructor
//
LocalMap::LocalMap()
{
    m_groundPlane = new GroundPlane;
    m_groundPlane->InitRenderComponent();
}

LocalMap::~LocalMap()
{
    m_groundPlane->ShutdownRenderComponent();
    delete m_groundPlane;
}

//
// callback from GameManager
//
void LocalMap::TradePostDidLoad(TradePostLocal *tradePost)
{
    // install the render component
    tradePost->InitRenderComponent();
}

void LocalMap::TradePostWillDelete(TradePostLocal *tradePost)
{
    // uninstall render component
    tradePost->ShutdownRenderComponent();
}

//
// controls
//
void LocalMap::FocusOnTradePost(TradePostLocal *tradePost)
{
    Camera* mainCam = GameRenderer::GetInstance()->GetMainCamera();
    mainCam->SetFocusPoint(tradePost->GetPos(), 15.0f);
}