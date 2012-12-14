//
//  DefaultShaderBasic.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/5/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "DefaultShaderBasic.h"
#include "ShaderManager.h"
#include "DefaultShaderIds.h"
#include "Shader.h"
#include <iostream>

namespace DefaultShader
{
    static const char* s_defaultBasicVsh = "\
    attribute vec4 position;\
    attribute vec3 normal;\
    \
    varying lowp vec4 colorVarying;\
    \
    uniform mat4 modelViewProjectionMatrix;\
    uniform vec4 lightColor;\
    void main()\
    {\
    vec3 vertexNormal = normalize(normal);\
    vec3 lightPosition = vec3(0.4, 1.0, 1.0);\
    vec4 diffuseColor = vec4(0.4, 0.4, 1.0, 1.0);\
    \
    float nDotVP = max(0.0, dot(vertexNormal, normalize(lightPosition)));\
    \
    colorVarying = lightColor * nDotVP;\
    \
    gl_Position = modelViewProjectionMatrix * position;\
    }";
    
    static const char* s_defaultBasicPsh = "\
    varying lowp vec4 colorVarying;\
    \
    void main()\
    {\
    gl_FragColor = colorVarying;\
    }";

    void InitBasicShader()
    {
        ShaderUniformDef uniformDefs[] = 
        {
            {
                SHADERVAR_VIEWPROJECTIONMATRIX, "modelViewProjectionMatrix"
            },
            {
                SHADERVAR_LIGHTCOLOR, "lightColor"
            },
            {
                SHADERVAR_NUM, NULL
            }
        };
        
        ShaderManager::GetInstance()->InitShaderProgram(s_defaultBasicVsh, s_defaultBasicPsh, DEFAULTSHADER_ID_BASIC, uniformDefs);
        
    }
    
    
}   // namespace DefaultShader
