//
//  Shape.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_Shape_h
#define broc_Shape_h

#include <OpenGLES/ES2/gl.h>

class Shape
{
public:
    Shape();
    Shape(const GLfloat* vertexData, unsigned int stride, unsigned int numVertices);
    Shape(const GLfloat* vertexBuffer, unsigned int vertexStride, unsigned int numVertices,
          const GLushort* indexBuffer, unsigned int indexStride, unsigned int numIndices, bool showDebugLines = false);
    virtual ~Shape();
    
    void CreateBuffers(const GLfloat* vertexBuffer, unsigned int vertexStride, unsigned int numVertices,
                       const GLushort* indexBuffer, unsigned int indexStride, unsigned int numIndices,
                       bool showDebugLines = false);
    
    // properties
    inline GLuint GetVAO()
    {
        return m_vertexArrayObject;
    }
    inline unsigned int GetNumVerts()
    {
        return m_numVerts;
    }
    inline unsigned int GetNumIndices()
    {
        return m_numIndices;
    }
    inline bool IsIndexed()
    {
        return (m_indexBuffer != 0);
    }
#if defined(DEBUG)
    inline GLuint GetDebugVAO()
    {
        return m_debugVAO;
    }
    inline unsigned int GetNumDebugIndices()
    {
        return m_numDebugIndices;
    }
#endif
    
protected:
    unsigned int m_numVerts;
    unsigned int m_numIndices;
    GLuint m_vertexArrayObject;
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    
#if defined(DEBUG)
    unsigned int m_numDebugIndices;
    GLuint m_debugVAO;
    GLuint m_debugIndexBuffer;
#endif

private:
    
};


#endif
