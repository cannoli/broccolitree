//
//  GameShaders.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/5/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "GameShaders.h"
#include "DefaultShaders.h"
#include <iostream>

namespace GameShader 
{
    void InitShaders()
    {
        DefaultShader::InitDefaultShaders();
        InitSimpleShader();
    }
}
