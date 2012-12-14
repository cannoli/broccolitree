//
//  GameRenderer.h
//  broc
//
//  This is the primary rendering manager for the broc game
//
//  Created by Shu Chiun Cheah on 4/4/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_GameRenderer_h
#define broc_GameRenderer_h
#include "RenderBucketIds.h"
#include "IRenderComponent.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <list>

class Camera;
class RenderCmdFactory;
class RenderCmd;
class LocalMap;
class TradePost;

class GameRenderer
{
public:
    static inline GameRenderer* GetInstance()
    {
        if(!singleton)
        {
            singleton = new GameRenderer;
        }
        return singleton;
    }
    static inline GameRenderer* CreateInstance()
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
    virtual ~GameRenderer();
    
    // properties
    inline RenderCmdFactory* GetCmdFactory()
    {
        return m_cmdFactory;
    }
    inline Camera* GetMainCamera()
    {
        return m_mainCamera;
    }
    inline void SetScreenWidth(float screenWidth)
    {
        m_screenWidth = screenWidth;
    }
    inline void SetScreenHeight(float screenHeight)
    {
        m_screenHeight = screenHeight;
    }
    inline float GetScreenWidth()
    {
        return m_screenWidth;
    }
    inline float GetScreenHeight()
    {
        return m_screenHeight;
    }
    
    // config
    void SetMainCameraPerspective(float fovy, float aspect, float near, float far);
    void SetMainCameraOrtho(float aspectScale, float aspect, float near, float far);
    
    // render components
    void AddRenderComponent(IRenderComponent* component);
    void RemoveRenderComponent(IRenderComponent* component);
    
    // per frame
    void AddDraw();
    void Render();
    
protected:
    // factories
    RenderCmdFactory* m_cmdFactory;
    
    // active render-components
    std::list<IRenderComponent*>* m_renderComponentList;
    
    Camera* m_mainCamera;
    float m_screenWidth;
    float m_screenHeight;
    
    // models (temporary, should be replaced with a world or scene structure)
    LocalMap* m_localMap;
    TradePost* m_tradePost;
    
private:
    static GameRenderer* singleton;
    GameRenderer();
};

#endif
