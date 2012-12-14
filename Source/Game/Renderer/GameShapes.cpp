//
//  GameShapes.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "GameShapes.h"
#include "ModelLib.h"
#include <iostream>

namespace GameShapes
{
    void LoadAllShapes()
    {
        ModelLib* lib = ModelLib::GetInstance();
        
        // Cube
        CubeShape* cube = new CubeShape;
        lib->AddShape(cube);
        
        // Rect
        RectShape* rect = new RectShape;
        lib->AddShape(rect);
    }
}
