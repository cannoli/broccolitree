//
//  RenderCmd.h
//  broc
//
//  This is an interface for all renderable objects that need to 
//  insert commands into RenderBuckets
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_RenderCmd_h
#define broc_RenderCmd_h

class RenderCmd
{
public:    
    RenderCmd();
    virtual ~RenderCmd();
    
    virtual void Reset() = 0;
    virtual void Execute() = 0;
};

#endif
