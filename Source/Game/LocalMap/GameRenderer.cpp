//
//  GameRenderer.cpp
//  broc
//
//  Notes:
//      The current ViewProjMatrix is on the top of the stack during RenderBucket->Execute
//
//  Created by Shu Chiun Cheah on 4/4/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "GameRenderer.h"
#include "Renderer.h"
#include "RenderCmdFactory.h"
#include "RenderContext.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "RenderBucketIds.h"
#include "GameShaderIds.h"
#include "Camera.h"
#include "LocalMap.h"
#include "TradePostLocal.h"
#include "GameShapes.h"
#include "ModelLib.h"
#include "GameShaders.h"
#include <iostream>
#include <assert.h>
#include "GLKMath.h"

#if defined(DEBUG)
#include "SimpleMaterialCmd.h"
#include "HudRectCmd.h"
#include "ModelLib.h"
#include "GameShapeIds.h"
#endif


static unsigned int GAMERENDERER_NUM_BUFFERS = 2;
static float MAINCAMERA_DEFAULT_PITCH = -M_PI_2 * 0.35f; // points downward (0.35 * Pi/2) radians
static float MAINCAMERA_DEFAULT_YAW = M_PI_2 * 0.1f;    // slightly northwest
static float MAINCAMERA_DEFAULT_DISTANCE = 15.0f;   // 10 meters
static float DEFAULT_SCREENWIDTH = 320.0f;
static float DEFAULT_SCREENHEIGHT = 480.0f;

//
// singleton
//
GameRenderer* GameRenderer::singleton = NULL;

//
// constructor/destructor
//
GameRenderer::GameRenderer()
{
    // init renderer low-level
    Renderer* renderer = Renderer::CreateInstance(RENDERBUCKET_NUM, GAMERENDERER_NUM_BUFFERS);
    
    // init shaders
    ShaderManager::CreateInstance(GAMESHADER_ID_NUM);
    GameShader::InitShaders();
    
    // init models
    ModelLib::CreateInstance(GAMESHAPE_NUM);
    GameShapes::LoadAllShapes();
    
    // init render buckets
    renderer->InitRenderBucket(RENDERBUCKET_SKY, 10);
    renderer->InitRenderBucket(RENDERBUCKET_BACKGROUND, 50);
    renderer->InitRenderBucket(RENDERBUCKET_HUD, 50);
    
    // init factories
    m_cmdFactory = new RenderCmdFactory;
    
    // init render components list
    m_renderComponentList = new std::list<IRenderComponent*>;
    
    // init camera
    m_mainCamera = new Camera(MAINCAMERA_DEFAULT_PITCH, MAINCAMERA_DEFAULT_YAW, MAINCAMERA_DEFAULT_DISTANCE);
    m_screenWidth = DEFAULT_SCREENWIDTH;
    m_screenHeight = DEFAULT_SCREENHEIGHT;
}

GameRenderer::~GameRenderer()
{
    delete m_cmdFactory;
    delete m_renderComponentList;
    delete m_mainCamera;
    ModelLib::DestroyInstance();
    ShaderManager::DestroyInstance();
    Renderer::DestroyInstance();
}

//
// config
//
void GameRenderer::SetMainCameraPerspective(float fovy, float aspect, float near, float far)
{
    m_mainCamera->SetPerspectiveParams(fovy, aspect, near, far);
}

void GameRenderer::SetMainCameraOrtho(float aspectScale, float aspect, float near, float far)
{
    m_mainCamera->SetOrthoParams(aspectScale, aspect, near, far);
}

//
// render components
//
void GameRenderer::AddRenderComponent(IRenderComponent *component)
{
    m_renderComponentList->push_back(component);
}

void GameRenderer::RemoveRenderComponent(IRenderComponent *component)
{
    m_renderComponentList->remove(component);
}

//
// per frame
//
void GameRenderer::AddDraw()
{
    // add cameras to buckets
    Renderer* renderer = Renderer::GetInstance();
    renderer->SetBucketMatrix(RENDERBUCKET_SKY, m_mainCamera->ViewProjectionMatrix());
    renderer->SetBucketMatrix(RENDERBUCKET_BACKGROUND, m_mainCamera->ViewProjectionMatrix());
    renderer->SetBucketMatrix(RENDERBUCKET_HUD, GLKMatrix4Identity);

    // add draw cmds to render buckets
    std::list<IRenderComponent*>::iterator it;
    for(it=m_renderComponentList->begin() ; it != m_renderComponentList->end(); it++)
    {
        (*it)->AddDraw();
    }
    
#if 0//defined(DEBUG)
    // testing only; add a rectangle to the Hud bucket
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

#endif
}

void GameRenderer::Render()
{
    // flip the draw buffer (so that game loop starts adding draw commands to the other buffer)
    GetCmdFactory()->FlipBuffer();
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.45f, 0.45f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Renderer::GetInstance()->Submit();
}