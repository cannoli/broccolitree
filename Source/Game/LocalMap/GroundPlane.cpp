//
//  GroundPlane.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/8/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "GroundPlane.h"
#include "ModelLib.h"
#include "GameShapeIds.h"
#include "Shape.h"
#include "PlaneShape.h"
#include "GameRenderer.h"
#include "SimpleMaterialCmd.h"
#include "GroundPlaneCmd.h"
#include "RenderCmdFactory.h"
#include "Renderer.h"
#include <iostream>

static const float GROUNDPLANE_WIDTH = 500.0f;
static const float GROUNDPLANE_LENGTH = 500.0f;
static const float GROUNDPLANE_SUBDIV_WIDTH = 5;
static const float GROUNDPLANE_SUBDIV_LENGTH = 5;

//
// constructor/destructor
//
GroundPlane::GroundPlane()
: m_model(NULL)
{
}

GroundPlane::~GroundPlane()
{
    if(m_model)
    {
        delete m_model;
    }
}

//
// rendering component
//
void GroundPlane::InitRenderComponent()
{
    m_model = new PlaneShape(GROUNDPLANE_WIDTH, GROUNDPLANE_LENGTH,
                             GROUNDPLANE_SUBDIV_WIDTH, GROUNDPLANE_SUBDIV_LENGTH);
    GameRenderer::GetInstance()->AddRenderComponent(this);    
}

void GroundPlane::ShutdownRenderComponent()
{
    GameRenderer::GetInstance()->RemoveRenderComponent(this);
    delete m_model;
    m_model = NULL;
}

void GroundPlane::AddDraw()
{
    if(m_model)
    {
        Renderer* renderer = Renderer::GetInstance();
        RenderCmdFactory* factory = GameRenderer::GetInstance()->GetCmdFactory();
        
        // set material
        SimpleMaterialCmd* material = reinterpret_cast<SimpleMaterialCmd*>(factory->NewCmd(RENDERCMD_SIMPLEMATERIAL));
        renderer->AddCmd(RENDERBUCKET_BACKGROUND, material);
        
        // geom
        GroundPlaneCmd* geom = reinterpret_cast<GroundPlaneCmd*>(factory->NewCmd(RENDERCMD_GROUNDPLANE));
        geom->SetModel(m_model);
        renderer->AddCmd(RENDERBUCKET_BACKGROUND, geom);
    }
}