//
//  Shader.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/5/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "Shader.h"
#include <iostream>
#include <OpenGLES/ES2/gl.h>

// constructor
//      uniformDef is a NULL terminated array of binding definitions
Shader::Shader(GLuint program, const ShaderUniformDef uniformDef[])
: m_program(program)
, m_numUniforms(0)
, m_uniforms(NULL)
{
    unsigned int count = 0;
    while(uniformDef[count].name != NULL)
    {
        ++count;
    }
    
    if(0 < count)
    {
        m_numUniforms = count;
        m_uniforms = new ShaderUniformBinding[count];
        
        for(unsigned int i = 0; i < count; ++i)
        {
            ShaderUniformBinding* binding = &(m_uniforms[i]);
            const ShaderUniformDef* def = &uniformDef[i];

            binding->uniformLocation = glGetUniformLocation(m_program, def->name);
            binding->shaderVarId = def->shaderVarId;
        }
    }
}

// destructor
Shader::~Shader()
{
    delete [] m_uniforms;
}
