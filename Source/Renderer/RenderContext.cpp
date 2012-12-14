//
//  RenderContext.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/3/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "RenderContext.h"
#include "Shader.h"
#include "DefaultShaderIds.h"
#include "GLKMath.h"
#include <iostream>
#include <assert.h>

RenderContext::RenderContext(unsigned int matrixStackSize, unsigned int maxShaderUniforms)
: m_maxShaderUniforms(maxShaderUniforms)
, m_curShader(NULL)
, m_matrixStackSize(matrixStackSize)
, m_matrixTop(0)
{
    m_shaderUniforms = new GLint[maxShaderUniforms];
    m_matrixStack = new GLKMatrix4[matrixStackSize];
}

RenderContext::~RenderContext()
{
    delete [] m_matrixStack;
    delete [] m_shaderUniforms;
}

//
// shader
//
/*
void RenderContext::LinkShaderVarToProgram(ShaderVar slot, GLuint program, const char* varName)
{
    m_ShaderUniforms[slot] = glGetUniformLocation(program, varName);
}

void RenderContext::SetShaderVarMatrix4(ShaderVar slot, const GLKMatrix4& matrix4)
{
    glUniformMatrix4fv(m_ShaderUniforms[slot], 1, 0, matrix4.m);
}
*/
void RenderContext::BindShader(Shader *shader)
{
    // store shader pointer
    m_curShader = shader;
    glUseProgram(shader->m_program);
    
    // bind shader uniforms
    for(unsigned int i = 0; i < shader->m_numUniforms; ++i)
    {
        unsigned int varSlot = shader->m_uniforms[i].shaderVarId;
        m_shaderUniforms[varSlot] = shader->m_uniforms[i].uniformLocation;
    }
}

GLint RenderContext::GetShaderUniform(unsigned int shaderVar)
{
    GLint result = -1;
    assert(m_maxShaderUniforms > shaderVar);
    if(m_maxShaderUniforms > shaderVar)
    {
        result = m_shaderUniforms[shaderVar];
    }
    return result;
}

//
// matrix
//
void RenderContext::PushMatrix(const GLKMatrix4 &matrix)
{
    assert(m_matrixTop < m_matrixStackSize);
    if(m_matrixTop < m_matrixStackSize)
    {
        m_matrixStack[m_matrixTop] = matrix;
        ++m_matrixTop;
    }
}

GLKMatrix4 RenderContext::PopMatrix()
{
    assert(0 < m_matrixTop);
    unsigned int top = m_matrixTop;
    --m_matrixTop;
    return (m_matrixStack[top]);
}

GLKMatrix4 RenderContext::TopMatrix()
{
    GLKMatrix4 result;
    if(0 < m_matrixTop)
    {
        result = m_matrixStack[m_matrixTop-1];
    }
    else 
    {
        result = GLKMatrix4Identity;
    }
    return (result);
}