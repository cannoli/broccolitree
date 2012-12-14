//
//  GroundPlaneCmd.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_GroundPlaneCmd_h
#define broc_GroundPlaneCmd_h

#include "RenderCmd.h"
#include <OpenGLES/ES2/gl.h>

class Shape;

class GroundPlaneCmd : public RenderCmd
{
public:
    GroundPlaneCmd();
    virtual ~GroundPlaneCmd();
    
    // properties
    inline void SetModel(Shape* model)
    {
        m_model = model;
    }
    
    // rendering
    virtual void Reset();
    virtual void Execute();

protected:
    Shape* m_model;
    
private:
    
};


#endif
