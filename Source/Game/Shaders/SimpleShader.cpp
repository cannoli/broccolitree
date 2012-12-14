//
//  SimpleShader.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/5/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "SimpleShader.h"
#include "ShaderManager.h"
#include "GameShaderIds.h"
#include "Shader.h"
#include <iostream>

namespace GameShader
{
    void InitSimpleShader()
    {
        ShaderUniformDef uniformDefs[] = 
        {
            {
                SHADERVAR_VIEWPROJECTIONMATRIX, "modelViewProjectionMatrix"
            },
            {
                GAMESHADERVAR_DIFFUSECOLOR, "diffuseColor"
            },
            {
                GAMESHADERVAR_NUM, NULL
            }
        };
        
        ShaderManager::GetInstance()->InitShaderProgramFromFile("Simple.vsh", "Simple.fsh", GAMESHADER_ID_SIMPLE, uniformDefs);
        
    }
    
    
}   // namespace DefaultShader
