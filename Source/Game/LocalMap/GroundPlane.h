//
//  GroundPlane.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/8/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_GroundPlane_h
#define broc_GroundPlane_h

#include "IRenderComponent.h"

class Shape;

class GroundPlane : public IRenderComponent
{
public:
    GroundPlane();
    ~GroundPlane();
    
    // render component
    virtual void InitRenderComponent();
    virtual void ShutdownRenderComponent();
    virtual void AddDraw();
    
protected:
    Shape* m_model;
    
private:
};


#endif
