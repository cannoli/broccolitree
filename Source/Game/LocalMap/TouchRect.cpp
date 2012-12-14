//
//  TouchRect.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/10/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//


#include "TouchRect.h"
#include "GLKMath.h"
#include "ModelLib.h"
#include "GameShapeIds.h"
#include "GameRenderer.h"
#include "Renderer.h"
#include "SimpleMaterialCmd.h"
#include "GameRenderCmdIds.h"
#include "HudRectCmd.h"
#include "RenderCmdFactory.h"
#include <iostream>

//
// constructor / destructor
//
TouchRect::TouchRect()
: m_origin(GLKVector2Make(0.0f, 0.0f))
, m_size(GLKVector2Make(1.0f, 1.0f))
, m_zDist(1.0f)
{
    m_model = ModelLib::GetInstance()->GetShape(GAMESHAPE_RECT);
}

TouchRect::~TouchRect()
{
    
}

//
// properties
//
void TouchRect::SetRect(float centerX, float centerY, float width, float height, float z)
{
    float halfWidth = 0.5f * width;
    float halfHeight = 0.5f * height;
    m_origin = GLKVector2Make(centerX - halfWidth, centerY - halfHeight);
    m_size = GLKVector2Make(width, height);
    m_zDist = z;
}

//
// touch test
//
bool TouchRect::DoesContainPoint(float pointX, float pointY) const
{
    bool result = true;
    float botLeftX = m_origin.x;
    float botLeftY = m_origin.y;
    float topRightX = m_origin.x + m_size.x;
    float topRightY = m_origin.y + m_size.y;
    if((pointX < botLeftX) ||
       (pointY < botLeftY) ||
       (pointX > topRightX) ||
       (pointY > topRightY))
    {
        result = false;
    }
    return result;
}


//
// rendering component
//
void TouchRect::InitRenderComponent()
{
    m_model = ModelLib::GetInstance()->GetShape(GAMESHAPE_RECT);
    GameRenderer::GetInstance()->AddRenderComponent(this);
}

void TouchRect::ShutdownRenderComponent()
{
    GameRenderer::GetInstance()->RemoveRenderComponent(this);
    m_model = NULL;
}

void TouchRect::AddDraw()
{
    if(m_model)
    {
        Renderer* renderer = Renderer::GetInstance();
        RenderCmdFactory* factory = GameRenderer::GetInstance()->GetCmdFactory();
        
        // set material
        SimpleMaterialCmd* material = reinterpret_cast<SimpleMaterialCmd*>(factory->NewCmd(RENDERCMD_SIMPLEMATERIAL));
        material->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
        renderer->AddCmd(RENDERBUCKET_HUD, material);
        
        // geom
        HudRectCmd* geom = reinterpret_cast<HudRectCmd*>(factory->NewCmd(RENDERCMD_HUDRECT));
        geom->SetTransform(GLKMatrix4Identity);
        geom->SetModel(ModelLib::GetInstance()->GetShape(GAMESHAPE_RECT));
        renderer->AddCmd(RENDERBUCKET_HUD, geom);        
    }
}
