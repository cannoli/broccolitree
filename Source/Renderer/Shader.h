//
//  Shader.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/5/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_Shader_h
#define broc_Shader_h

#include <OpenGLES/ES2/gl.h>

struct ShaderUniformDef
{
    unsigned int shaderVarId;   // the identifier ShaderManager uses to interface the game
                                // with this uniform
    const char* name;           // name of this variable in the GL shader program source code
};

struct ShaderUniformBinding
{
    unsigned int shaderVarId;   // the identifier ShaderManager uses to interface the game
                                // with this uniform
    GLint uniformLocation;      // location of uniform in the GL shader program    
};

class RenderContext;

class Shader
{
public:
    Shader(GLuint program, const ShaderUniformDef uniformDef[]);
    ~Shader();
    
protected:
    GLuint m_program;
    unsigned int m_numUniforms;
    ShaderUniformBinding* m_uniforms;
    
    friend class RenderContext;
};

#endif
