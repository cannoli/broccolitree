//
//  HudRectCmd.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/10/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_HudRectCmd_h
#define broc_HudRectCmd_h

#include "RenderCmd.h"
#include "GLKMathTypes.h"
#include <OpenGLES/ES2/gl.h>

class Shape;
class HudRectCmd : public RenderCmd
{
public:
    HudRectCmd();
    virtual ~HudRectCmd();
    
    // properties
    inline void SetTransform(const GLKMatrix4& transform)
    {
        m_transform = transform;
    }
    inline void SetModel(Shape* model)
    {
        m_model = model;
    }
    
    // rendering
    virtual void Reset();
    virtual void Execute();
    
protected:
    Shape* m_model;
    GLKMatrix4 m_transform;
    
private:

};

#endif
