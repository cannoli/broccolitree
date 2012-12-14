//
//  IRenderComponent.h
//  broc
//
//  Common interface for all the rendering components in game objects
//      
//  Created by Shu Chiun Cheah on 4/8/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_IRenderComponent_h
#define broc_IRenderComponent_h

class IRenderComponent
{
public:
    virtual void InitRenderComponent() = 0;
    virtual void ShutdownRenderComponent() = 0;
    virtual void AddDraw() = 0;
};

#endif
