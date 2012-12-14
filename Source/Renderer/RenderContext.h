//
//  RenderContext.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/3/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_RenderContext_h
#define broc_RenderContext_h

#include "GLKMathTypes.h"
#include <OpenGLES/ES2/gl.h>


class Shader;

class RenderContext
{    
    // shader
    unsigned int m_maxShaderUniforms;
    GLint* m_shaderUniforms;
    Shader* m_curShader;
    
    // matrix
    unsigned int m_matrixStackSize;
    unsigned int m_matrixTop;
    GLKMatrix4* m_matrixStack;
    
public:
    RenderContext(unsigned int matrixStackSize, unsigned int maxShaderUniforms);
    ~RenderContext();
    
    // shader
    void BindShader(Shader* shader);
    GLint GetShaderUniform(unsigned int shaderId);
    
    // matrix
    void PushMatrix(const GLKMatrix4& matrix);
    GLKMatrix4 PopMatrix();
    GLKMatrix4 TopMatrix();
};

#endif
