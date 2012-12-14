//
//  TradePostCmd.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "TradePostCmd.h"
#include "Renderer.h"
#include "ModelLib.h"
#include "GameShapeIds.h"
#include "Shape.h"
#include "GLKMath.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

//
// constructor/destructor
//
TradePostCmd::TradePostCmd()
: RenderCmd()
, m_model(NULL)
, m_transform(GLKMatrix4Identity)
{
}

TradePostCmd::~TradePostCmd()
{
    
}


//
// rendering
//
void TradePostCmd::Reset()
{
}

void TradePostCmd::Execute()
{
    if(m_model)
    {
        RenderContext* context = Renderer::GetInstance()->GetContext();
        
        GLint modelViewProjVar = context->GetShaderUniform(SHADERVAR_VIEWPROJECTIONMATRIX);
        GLKMatrix4 mtx = GLKMatrix4Multiply(context->TopMatrix(), m_transform);
        glUniformMatrix4fv(modelViewProjVar, 1, 0, mtx.m);
        
        glBindVertexArrayOES(m_model->GetVAO());
        glDrawArrays(GL_TRIANGLES, 0, m_model->GetNumVerts());
    }
}