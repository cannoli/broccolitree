//
//  SimpleMaterialCmd.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "SimpleMaterialCmd.h"
#include "Renderer.h"
#include "GameShaderIds.h"
#include <iostream>

//
// constructor/destructor
//
SimpleMaterialCmd::SimpleMaterialCmd()
: RenderCmd()
{
    m_diffuse = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
}

SimpleMaterialCmd::~SimpleMaterialCmd()
{
    
}

//
// properties
//
void SimpleMaterialCmd::SetDiffuse(float r, float g, float b, float a)
{
    m_diffuse = GLKVector4Make(r, g, b, a);
}

//
// rendering
//
void SimpleMaterialCmd::Reset()
{
    m_diffuse = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
}

void SimpleMaterialCmd::Execute()
{
    RenderContext* context = Renderer::GetInstance()->GetContext();
    
    // set shader
    Shader* basicShader = ShaderManager::GetInstance()->GetShader(GAMESHADER_ID_SIMPLE);
    context->BindShader(basicShader);

    // set material variables
    GLint lightColorVar = context->GetShaderUniform(GAMESHADERVAR_DIFFUSECOLOR);
    glUniform4fv(lightColorVar, 1, m_diffuse.v);
}