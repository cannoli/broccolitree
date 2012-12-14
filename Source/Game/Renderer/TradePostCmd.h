//
//  TradePostCmd.h
//  broc
//
//  TradePost render command; this is the Render-Loop portion of rendering;
//  called between beginFrame and endFrame
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_TradePostCmd_h
#define broc_TradePostCmd_h


#include "RenderCmd.h"
#include "GLKMathTypes.h"
#include <OpenGLES/ES2/gl.h>

class Shape;
class TradePostCmd : public RenderCmd
{
public:
    TradePostCmd();
    virtual ~TradePostCmd();
    
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
