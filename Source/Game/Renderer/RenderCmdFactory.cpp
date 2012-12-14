//
//  RenderCmdFactory.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "RenderCmdFactory.h"
#include "Renderer.h"
#include "RenderCmd.h"
#include <iostream>
#include <assert.h>

// commands
#include "GameRenderCmds.h"

//
// constructor/destructor
// 
RenderCmdFactory::RenderCmdFactory()
{
    m_numBuffers = Renderer::GetInstance()->GetNumBuffers();
    m_curBuffer = 0;
    CreatePools();
}

RenderCmdFactory::~RenderCmdFactory()
{
    for(unsigned int cmdType = 0; cmdType < RENDERCMD_NUM; ++cmdType)
    {
        for(unsigned int buffer = 0; buffer < m_numBuffers; ++buffer)
        {
            delete [] m_cmdPools[cmdType][buffer];
        }
        delete [] m_cmdPools[cmdType];
    }
}

//
// private methods
//
void RenderCmdFactory::CreatePools()
{
    // init pool sizes
    m_cmdPoolSize[RENDERCMD_GROUNDPLANE] = 1;
    m_cmdPoolSize[RENDERCMD_SIMPLEMATERIAL] = 40;
    m_cmdPoolSize[RENDERCMD_TRADEPOST] = 20;
    m_cmdPoolSize[RENDERCMD_HUDRECT] = 20;
    
    // create cmd pool arrays per buffer
    for(unsigned int cmdType = 0; cmdType < RENDERCMD_NUM; ++cmdType)
    {
        m_cmdPools[cmdType] = new RenderCmd**[m_numBuffers];
        for(unsigned int buffer = 0; buffer < m_numBuffers; ++buffer)
        {
            m_cmdPools[cmdType][buffer] = new RenderCmd* [m_cmdPoolSize[cmdType]];
        }
    }
    
    // init next-free indices per cmd type
    for(unsigned int cmdType = 0; cmdType < RENDERCMD_NUM; ++cmdType)
    {
        m_cmdPoolNext[cmdType] = 0;
    }
    
    // now create the actual pools
    for(unsigned int buffer = 0; buffer < m_numBuffers; ++buffer)
    {
        unsigned int numEntries;

        // GroundPlane
        numEntries = m_cmdPoolSize[RENDERCMD_GROUNDPLANE];
        for(unsigned int entry = 0; entry < numEntries; ++entry)
        {
            m_cmdPools[RENDERCMD_GROUNDPLANE][buffer][entry] = new GroundPlaneCmd;
        }
        
        // SimpleMaterial
        numEntries = m_cmdPoolSize[RENDERCMD_SIMPLEMATERIAL];
        for(unsigned int entry = 0; entry < numEntries; ++entry)
        {
            m_cmdPools[RENDERCMD_SIMPLEMATERIAL][buffer][entry] = new SimpleMaterialCmd;
        }
        
        // TradePost
        numEntries = m_cmdPoolSize[RENDERCMD_TRADEPOST];
        for(unsigned int entry = 0; entry < numEntries; ++entry)
        {
            m_cmdPools[RENDERCMD_TRADEPOST][buffer][entry] = new TradePostCmd;
        }
        
        // HudRect
        numEntries = m_cmdPoolSize[RENDERCMD_HUDRECT];
        for(unsigned int entry = 0; entry < numEntries; ++entry)
        {
            m_cmdPools[RENDERCMD_HUDRECT][buffer][entry] = new HudRectCmd;
        }
    }
}

//
// public methods
//
RenderCmd* RenderCmdFactory::NewCmd(unsigned int renderCmdId)
{
    unsigned int buffer = m_curBuffer;
    RenderCmd* result = NULL;
    assert(RENDERCMD_NUM > renderCmdId);
    if(RENDERCMD_NUM > renderCmdId)
    {
        RenderCmd** curPool = m_cmdPools[renderCmdId][buffer];
        unsigned int next = m_cmdPoolNext[renderCmdId];
        assert(next < m_cmdPoolSize[renderCmdId]);
        if(next < m_cmdPoolSize[renderCmdId])
        {
            // allocate
            result = curPool[next];
            
            // reset the content of this command to default values because we are reusing cmd chunks from previous frames
            result->Reset();
            
            ++next;
            m_cmdPoolNext[renderCmdId] = next;
        }
    }
    return result;
}

void RenderCmdFactory::FlipBuffer()
{
    unsigned int buffer = m_curBuffer + 1;
    if(buffer >= m_numBuffers)
    {
        buffer = 0;
    }
    
    // reset allocations
    for(unsigned int cmdType = 0; cmdType < RENDERCMD_NUM; ++cmdType)
    {
        m_cmdPoolNext[cmdType] = 0;
    }
}
