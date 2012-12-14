//
//  GameShaderIds.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/4/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_GameShaderIds_h
#define broc_GameShaderIds_h

#include "DefaultShaderIds.h"

typedef enum _shaderIds
{
    GAMESHADER_ID_BEGIN = DEFAULTSHADER_ID_NUM,
    GAMESHADER_ID_SIMPLE = GAMESHADER_ID_BEGIN,
    GAMESHADER_ID_NUM
} GameShaderIds;

enum _GameShaderVars
{
    // global shader variables
    GAMESHADERVAR_BEGIN = SHADERVAR_NUM,
    GAMESHADERVAR_DIFFUSECOLOR,
    GAMESHADERVAR_NUM
};


#endif
