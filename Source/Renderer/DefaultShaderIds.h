//
//  DefaultShaderIds.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/3/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_DefaultShaderIds_h
#define broc_DefaultShaderIds_h

typedef enum _DefaultShaders
{
    DEFAULTSHADER_ID_BASIC = 0,
    DEFAULTSHADER_ID_NUM
} DefaultShaderIds;

enum _DefaultShaderVars
{
    // global shader variables
    SHADERVAR_VIEWPROJECTIONMATRIX,
    SHADERVAR_LIGHTCOLOR,
    SHADERVAR_NUM
};


#endif
