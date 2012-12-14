//
//  Renderer.h
//  broc
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_Renderer_h
#define broc_Renderer_h

#include "RenderContext.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "RenderBucket.h"
#include "DefaultShaders.h"
#include "GLKMath.h"

class RenderContext;
class RenderBucket;
class RenderCmd;
class Renderer
{
public:
    // singleton
    static inline Renderer* CreateInstance(unsigned int numBuckets, unsigned int numBuffers)
    {
        if(!singleton)
        {
            singleton = new Renderer(numBuckets, numBuffers);
        }
        return singleton;
    }
    static inline Renderer* GetInstance()
    {
        if(!singleton)
        {
            singleton = new Renderer(10, 2);
        }
        return singleton;
    }
    static void DestroyInstance();
    virtual ~Renderer();

    // properties
    inline RenderContext* GetContext()
    {
        return m_renderContext;
    }
    inline unsigned int GetCurBuffer()
    {
        return m_curBuffer;
    }
    inline unsigned int GetNumBuffers()
    {
        return m_numBuffers;
    }
    
    // init functions
    void InitRenderBucket(unsigned int bucketId, unsigned int maxEntries);
    
    // rendering
    void SetBucketMatrix(unsigned int bucketId, const GLKMatrix4& matrix);
    void AddCmd(unsigned int bucketId, RenderCmd* cmd);
    void Submit();
    
protected:
    RenderContext*  m_renderContext;
    RenderBucket*** m_renderBuckets;    // [buffer][bucket][cmd]
    unsigned int    m_numBuckets;
    unsigned int    m_numBuffers;       // number of render buffers
    unsigned int    m_curBuffer;        // this is the current insertion buffer
    
private:
    static Renderer* singleton;
    Renderer(unsigned int numBuckets, unsigned int numBuffers);
};

#endif
