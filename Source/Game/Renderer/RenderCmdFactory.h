//
//  RenderCmdFactory.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_RenderCmdFactory_h
#define broc_RenderCmdFactory_h

#include "GameRenderCmdIds.h"

// command types
class GroundPlaneCmd;
class SimpleMaterialCmd;
class RenderCmd;

// class
class RenderCmdFactory
{
public:
    RenderCmdFactory();
    virtual ~RenderCmdFactory();
    
    RenderCmd* NewCmd(unsigned int renderCmdId);
    void FlipBuffer();
    
protected:
    unsigned int m_numBuffers;
    unsigned int m_curBuffer;
    
    // cmd pools
    RenderCmd***  m_cmdPools[RENDERCMD_NUM];
    unsigned int m_cmdPoolSize[RENDERCMD_NUM];
    unsigned int m_cmdPoolNext[RENDERCMD_NUM];
    
private:
    void CreatePools();
};

#endif
