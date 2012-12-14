//
//  ShaderManager.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/3/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_ShaderManager_h
#define broc_ShaderManager_h

#include "DefaultShaderIds.h"
#include <OpenGLES/ES2/gl.h>


struct ShaderUniformDef;
class Shader;

class ShaderManager
{
public:    
    static inline ShaderManager* CreateInstance(unsigned int numShaders)
    {
        if(!singleton)
        {
            singleton = new ShaderManager(numShaders);
        }
        return singleton;
    }
    static inline ShaderManager* GetInstance()
    {
        if(!singleton)
        {
            singleton = new ShaderManager(DEFAULTSHADER_ID_NUM);
        }
        return singleton;
    }
    static void DestroyInstance();
    virtual ~ShaderManager();
    
    void InitShaderProgramFromFile(const char* vshFilename, const char* fshFilename,
                                   unsigned int shaderId, const ShaderUniformDef uniformDefs[]);
    void InitShaderProgram(const GLchar* vshSource, const GLchar* pshSource, 
                           unsigned int shaderId, const ShaderUniformDef uniformDefs[]);
    void BindShader(unsigned int shaderId);
    GLint GetShaderUniform(const char* varName);
    
    // shader
    Shader* GetShader(unsigned int shaderId);
    
protected:
    unsigned int m_numShaders;
    GLuint* m_programs;
    GLuint  m_boundProgram;
    Shader** m_shaders;

    bool CompileShader(GLuint* shader, GLenum shaderType, const GLchar* source);
    static void ValidateShaderProgram(GLuint programId);
    
private:
    static ShaderManager* singleton;
    ShaderManager(unsigned int numShaders);
};


#endif
