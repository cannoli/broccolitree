//
//  SimpleMaterialCmd.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_SimpleMaterialCmd_h
#define broc_SimpleMaterialCmd_h

#include "RenderCmd.h"
#include "GLKMathTypes.h"

class SimpleMaterialCmd : public RenderCmd
{
public:
    SimpleMaterialCmd();
    virtual ~SimpleMaterialCmd();
    
    // properties
    void SetDiffuse(float r, float g, float b, float a);
    
    // rendering
    virtual void Reset();
    virtual void Execute();
    
protected:
    GLKVector4 m_diffuse;
    
private:
    
};


#endif
