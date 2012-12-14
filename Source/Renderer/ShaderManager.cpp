//
//  ShaderManager.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/3/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "ShaderManager.h"
#include "DefaultShaderIds.h"
#include "DefaultShaders.h"
#include "Shader.h"
#include "VertexAttributes.h"
#include "FileResource.h"
#include <OpenGLES/ES2/gl.h>
#include <iostream>
#include <assert.h>


//
// singleton
//
ShaderManager* ShaderManager::singleton = NULL;

void ShaderManager::DestroyInstance()
{
    if(singleton)
    {
        delete singleton;
    }
    singleton = NULL;
}

//
// constructor/destructor
//
ShaderManager::ShaderManager(unsigned int numShaders)
: m_numShaders(numShaders)
{
    m_programs = new GLuint[numShaders];
    m_shaders = new Shader*[numShaders];
    
    // the shader programs are not created here;
    // the caller renderer is responsible for creating them and populate the shaders registry
}

ShaderManager::~ShaderManager()
{
    for(unsigned int i = 0; i < m_numShaders; ++i)
    {
        delete m_shaders[i];
        glDeleteProgram(m_programs[i]);
    }
    delete [] m_shaders;
    delete [] m_programs;
}

//
// shader initializers
//
void ShaderManager::InitShaderProgramFromFile(const char *vshFilename, const char *fshFilename, 
                                              unsigned int shaderId, const ShaderUniformDef *uniformDefs)
{
    FileResource* vsh = new FileResource(vshFilename);
    FileResource* fsh = new FileResource(fshFilename);
    this->InitShaderProgram(vsh->GetContentAsUTF8String(), fsh->GetContentAsUTF8String(), shaderId, uniformDefs);
    
    delete fsh;
    delete vsh;
}

void ShaderManager::InitShaderProgram(const GLchar* vshSource, const GLchar* pshSource, 
                                      unsigned int shaderId, const ShaderUniformDef uniformDefs[])
{
    assert(shaderId < m_numShaders);
    
    GLuint vertShader, fragShader;
    bool vshResult = CompileShader(&vertShader, GL_VERTEX_SHADER, vshSource);
    bool pshResult = CompileShader(&fragShader, GL_FRAGMENT_SHADER, pshSource);

    assert(vshResult && pshResult);
    if(vshResult && pshResult)
    {
        GLuint programId = glCreateProgram();
        glAttachShader(programId, vertShader);
        glAttachShader(programId, fragShader);
        
        // bind vertex attributes
        glBindAttribLocation(programId, VTXATTRIB_POSITION, "position");
        glBindAttribLocation(programId, VTXATTRIB_NORMAL, "normal");

        
        GLint linkStatus;
        glLinkProgram(programId);
        glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
        assert(linkStatus);
#if defined(DEBUG)
        if(0 == linkStatus)
        {
            GLint logLength;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) 
            {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetProgramInfoLog(programId, logLength, &logLength, log);
                std::cout << "Program link log:" << std::endl << log;
                free(log);
            }
        }
#endif

        // store program id in the shader registry
        m_programs[shaderId] = programId;
        
        // create shader instance
        m_shaders[shaderId] = new Shader(programId, uniformDefs);
        
        // release vertex and fragment shaders, no longer needed
        glDetachShader(programId, vertShader);
        glDeleteShader(vertShader);
        glDetachShader(programId, fragShader);
        glDeleteShader(fragShader);
    }
}

bool ShaderManager::CompileShader(GLuint* shader, GLenum shaderType, const GLchar* source)
{
    bool result = true;
    *shader = glCreateShader(shaderType);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) 
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        std::cout << "Shader compile log:" << std::endl << log;
        free(log);
    }
#endif

    GLint status = 0;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if(status == 0)
    {
        // if compile error, delete shader and exit
        glDeleteShader(*shader);
        result = false;
    }
    return result;
}


void ShaderManager::ValidateShaderProgram(GLuint prog)
{
#if defined (DEBUG)
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) 
    {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        std::cout << "Program validate log:" << std::endl << log;
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    assert(status);
    if (status == 0) 
    {
        std::cout << "Program validate error" << std::endl;
    }
#endif
}

//
// submission
//
void ShaderManager::BindShader(unsigned int shaderId)
{
    if(m_numShaders > shaderId)
    {
        // bind program to GL
        glUseProgram(m_programs[shaderId]);
        m_boundProgram = m_programs[shaderId];
    }
}

GLint ShaderManager::GetShaderUniform(const char *varName)
{
    GLint result = glGetUniformLocation(m_boundProgram, varName);
    return result;
}

Shader* ShaderManager::GetShader(unsigned int shaderId)
{
    Shader* result = NULL;
    assert(m_numShaders > shaderId);
    if(m_numShaders > shaderId)
    {
        result = m_shaders[shaderId];
    }
    return result;
}
