//
//  HudRectCmd.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/10/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "HudRectCmd.h"
#include "Renderer.h"
#include "ModelLib.h"
#include "GameShapeIds.h"
#include "GameShaderIds.h"
#include "Shape.h"
#include "GLKMath.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

//
// constructor/destructor
//
HudRectCmd::HudRectCmd()
: RenderCmd()
, m_model(NULL)
, m_transform(GLKMatrix4Identity)
{
}

HudRectCmd::~HudRectCmd()
{
    
}


//
// rendering
//
void HudRectCmd::Reset()
{
}

void HudRectCmd::Execute()
{
    if(m_model)
    {
        RenderContext* context = Renderer::GetInstance()->GetContext();
        
        GLint modelViewProjVar = context->GetShaderUniform(SHADERVAR_VIEWPROJECTIONMATRIX);
        //GLKMatrix4 proj = GLKMatrix4MakeOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        //proj = GLKMatrix4Multiply(proj, m_transform);
        //glUniformMatrix4fv(modelViewProjVar, 1, 0, proj.m);
        glUniformMatrix4fv(modelViewProjVar, 1, 0, m_transform.m);
        glBindVertexArrayOES(m_model->GetVAO());
        if(m_model->IsIndexed())
        {
            //glDrawElements(GL_TRIANGLE_FAN, m_model->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
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
            glDrawArrays(GL_TRIANGLE_FAN, 0, m_model->GetNumVerts());
        }
    }
}