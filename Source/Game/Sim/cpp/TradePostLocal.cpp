//
//  TradePostLocal.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "TradePostLocal.h"
#include "GameRenderer.h"
#include "Renderer.h"
#include "RenderCmdFactory.h"
#include "SimpleMaterialCmd.h"
#include "TradePostCmd.h"
#include "HudRectCmd.h"
#include "Vec3.h"
#include "PlaneShape.h"
#include "Shape.h"
#include "ModelLib.h"
#include "GameShapeIds.h"
#include "TouchRect.h"
#include <iostream>

//
// constructor/destructor
//
TradePostLocal::TradePostLocal()
: m_model(NULL)
, m_pos(0.0f, 0.0f, 0.0f)
, m_transform(GLKMatrix4Identity)
, m_touchRect(NULL)
, m_name(NULL)
{
}

TradePostLocal::TradePostLocal(float x, float y, float z)
: m_model(NULL)
, m_pos(x, y, z)
, m_transform(GLKMatrix4Identity)
, m_touchRect(NULL)
, m_name(NULL)
{
}

TradePostLocal::~TradePostLocal()
{
    if(m_touchRect)
    {
        delete m_touchRect;
    }
    // no need to delete m_model here because we don't own it
}

void* TradePostLocal::operator new (size_t sz, void* object)
{
    return object;
}

//
// properties
//
const TouchRect* TradePostLocal::RefreshTouchRect(GLKMatrix4 viewProjMatrix)
{
    if(!m_touchRect)
    {
        m_touchRect = new TouchRect();
    }
    GLKVector3 projectedPos = GLKMatrix4MultiplyAndProjectVector3(viewProjMatrix, m_pos.AsGLKVector3());
    
    float screenWidth = GameRenderer::GetInstance()->GetScreenWidth();
    float screenHeight = GameRenderer::GetInstance()->GetScreenHeight();

    // this equation here scales up the touch-rect size as it gets closer (lower projected-z)
    // touch-rect size is low-clamped at 0.1f to prevent it from becoming too small when the tradepost
    // is too far away
    float screenWidthFactor = (-10.0f * projectedPos.z) + 10.0f;
    if(screenWidthFactor < 0.1f)
    {
        screenWidthFactor = 0.1f;
    }
    float rectScreenWidth = screenWidthFactor * screenWidth;
    float rectViewWidth = 2.0f * (rectScreenWidth / screenWidth);   // multiplied by 2 because the projected space span is -1.0f to 1.0f
    float rectViewHeight = 2.0f * (rectScreenWidth / screenHeight);
    
    m_touchRect->SetRect(projectedPos.x, projectedPos.y, rectViewWidth, rectViewHeight, projectedPos.z);
    return m_touchRect;
}


//
// rendering component
//
void TradePostLocal::InitRenderComponent()
{
    m_model = ModelLib::GetInstance()->GetShape(GAMESHAPE_CUBE);
    GameRenderer::GetInstance()->AddRenderComponent(this);
}

void TradePostLocal::ShutdownRenderComponent()
{
    GameRenderer::GetInstance()->RemoveRenderComponent(this);
    m_model = NULL;
}

void TradePostLocal::AddDraw()
{
    if(m_model)
    {
        Renderer* renderer = Renderer::GetInstance();
        RenderCmdFactory* factory = GameRenderer::GetInstance()->GetCmdFactory();
        
        // set material
        SimpleMaterialCmd* material = reinterpret_cast<SimpleMaterialCmd*>(factory->NewCmd(RENDERCMD_SIMPLEMATERIAL));
        material->SetDiffuse(0.2f, 0.2f, 1.0f, 1.0f);
        renderer->AddCmd(RENDERBUCKET_BACKGROUND, material);
        
        // geom
        TradePostCmd* geom = reinterpret_cast<TradePostCmd*>(factory->NewCmd(RENDERCMD_TRADEPOST));
        GLKMatrix4 transform = GLKMatrix4Translate(m_transform, m_pos.GetX(), m_pos.GetY(), m_pos.GetZ());
        geom->SetTransform(transform);
        geom->SetModel(m_model);
        renderer->AddCmd(RENDERBUCKET_BACKGROUND, geom);  
        
        if(m_touchRect)
        {
            // set material
            SimpleMaterialCmd* material = reinterpret_cast<SimpleMaterialCmd*>(factory->NewCmd(RENDERCMD_SIMPLEMATERIAL));
            material->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
            renderer->AddCmd(RENDERBUCKET_HUD, material);
            
            // geom
            HudRectCmd* geom = reinterpret_cast<HudRectCmd*>(factory->NewCmd(RENDERCMD_HUDRECT));
            float sizeX = m_touchRect->GetSize().x;
            float sizeY = m_touchRect->GetSize().y;
            GLKMatrix4 rectTransform = GLKMatrix4MakeTranslation(m_touchRect->GetOrigin().x + (sizeX * 0.5f), m_touchRect->GetOrigin().y + (sizeY * 0.5f), 0.0f);
            rectTransform = GLKMatrix4Scale(rectTransform, sizeX, sizeY, 1.0f);
            geom->SetTransform(rectTransform);
            geom->SetModel(ModelLib::GetInstance()->GetShape(GAMESHAPE_RECT));
            renderer->AddCmd(RENDERBUCKET_HUD, geom);        
        }
        
    }
}
