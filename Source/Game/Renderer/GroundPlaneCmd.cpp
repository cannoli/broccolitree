//
//  GroundPlaneCmd.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "GroundPlaneCmd.h"
#include "Renderer.h"
#include "GameShaderIds.h"
#include "Shape.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <iostream>

//
// constructor/destructor
//
GroundPlaneCmd::GroundPlaneCmd()
: RenderCmd()
, m_model(NULL)
{
    
}

GroundPlaneCmd::~GroundPlaneCmd()
{
    
}


//
// rendering
//
void GroundPlaneCmd::Reset()
{
}

void GroundPlaneCmd::Execute()
{
    if(m_model)
    {
        RenderContext* context = Renderer::GetInstance()->GetContext();
        
        GLint modelViewProjVar = context->GetShaderUniform(SHADERVAR_VIEWPROJECTIONMATRIX);
        glUniformMatrix4fv(modelViewProjVar, 1, 0, context->TopMatrix().m);
        
        glBindVertexArrayOES(m_model->GetVAO());
        if(m_model->IsIndexed())
        {
            glDrawElements(GL_TRIANGLES, m_model->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
#if defined(DEBUG)
            if(m_model->GetDebugVAO())
            {    
                // disable depth for debug draw
                glDisable(GL_DEPTH_TEST);
                
                // set material variables
                GLint lightColorVar = context->GetShaderUniform(GAMESHADERVAR_DIFFUSECOLOR);
                glUniform4f(lightColorVar, 0.8f, 0.6f, 0.6f, 1.0f);

                glLineWidth(1.0f);
                glBindVertexArrayOES(m_model->GetDebugVAO());
                glDrawElements(GL_LINES, m_model->GetNumDebugIndices(), GL_UNSIGNED_SHORT, 0);
                
                // re-enable depth
                glEnable(GL_DEPTH_TEST);
            }
#endif
        }
        else 
        {
            glDrawArrays(GL_TRIANGLES, 0, m_model->GetNumVerts());
        }
    }
}