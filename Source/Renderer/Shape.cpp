//
//  Shape.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/6/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "Shape.h"
#include "VertexAttributes.h"
#include <OpenGLES/ES2/glext.h>
#include <iostream>
#include <assert.h>

#if defined(DEBUG)
static bool sDebugShapeVerbose = false;
#endif

//
// constructor/destructor
//
Shape::Shape()
: m_numVerts(0)
, m_numIndices(0)
, m_vertexArrayObject(0)
, m_vertexBuffer(0)
, m_indexBuffer(0)
#if defined(DEBUG)
, m_numDebugIndices(0)
, m_debugVAO(0)
, m_debugIndexBuffer(0)
#endif
{
    // subclass is responsible for calling CreateBuffers() to fill in the content
}

Shape::Shape(const GLfloat* vertexData, unsigned int stride, unsigned int numVertices)
: m_numVerts(numVertices)
{
    glGenVertexArraysOES(1, &m_vertexArrayObject);
    glBindVertexArrayOES(m_vertexArrayObject);
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, stride * numVertices, vertexData, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(VTXATTRIB_POSITION);
    glVertexAttribPointer(VTXATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(VTXATTRIB_NORMAL);
    glVertexAttribPointer(VTXATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)(sizeof(float) * 3));
    
    glBindVertexArrayOES(0);
    
    m_indexBuffer = 0;
    m_numIndices = 0;
#if defined(DEBUG)
    m_numDebugIndices = 0;
    m_debugVAO = 0;
    m_debugIndexBuffer = 0;
#endif
}

Shape::Shape(const GLfloat* vertexBuffer, unsigned int vertexStride, unsigned int numVertices,
             const GLushort* indexBuffer, unsigned int indexStride, unsigned int numIndices,
             bool showDebugLines)
{
    CreateBuffers(vertexBuffer, vertexStride, numVertices, indexBuffer, indexStride, numIndices, showDebugLines);
}

Shape::~Shape()
{
#if defined(DEBUG)
    if(m_debugIndexBuffer)
    {
        glDeleteBuffers(1, &m_debugIndexBuffer);
    }
    if(m_debugVAO)
    {
        glDeleteVertexArraysOES(1, &m_debugVAO);
    }
#endif
    if(m_indexBuffer)
    {
        glDeleteBuffers(1, &m_indexBuffer);
    }
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteVertexArraysOES(1, &m_vertexArrayObject);
}

void Shape::CreateBuffers(const GLfloat *vertexBuffer, unsigned int vertexStride, unsigned int numVertices, 
                          const GLushort *indexBuffer, unsigned int indexStride, unsigned int numIndices,
                          bool showDebugLines)
{
    m_numVerts = numVertices;
    m_numIndices = numIndices;
    glGenVertexArraysOES(1, &m_vertexArrayObject);
    glBindVertexArrayOES(m_vertexArrayObject);
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexStride * numVertices, vertexBuffer, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(VTXATTRIB_POSITION);
    glVertexAttribPointer(VTXATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(VTXATTRIB_NORMAL);
    glVertexAttribPointer(VTXATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)(sizeof(float) * 3));
    
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexStride * numIndices, indexBuffer, GL_STATIC_DRAW);
    
#if defined(DEBUG)
    if(showDebugLines)
    {
        glBindVertexArrayOES(0);    

        // assume indexbuffer represents a TRIANGLES list
        m_numDebugIndices = numIndices * 2;
        GLushort* debugIndices = new GLushort[m_numDebugIndices];
        unsigned int cur = 0;
        unsigned int debugIndex = 0;
        while(cur < numIndices)
        {
            assert((debugIndex +5) < m_numDebugIndices);
                   
            // edge 1
            debugIndices[debugIndex] = indexBuffer[cur];
            debugIndices[debugIndex+1] = indexBuffer[cur+1];
            
            // edge 2
            debugIndices[debugIndex+2] = indexBuffer[cur+1];
            debugIndices[debugIndex+3] = indexBuffer[cur+2];
            
            // edge 3
            debugIndices[debugIndex+4] = indexBuffer[cur+2];
            debugIndices[debugIndex+5] = indexBuffer[cur];
            
            debugIndex += 6;
            cur += 3;
        }
        
        if(sDebugShapeVerbose)
        {
            for(unsigned int i = 0; i < m_numDebugIndices; ++i)
            {
                std::cout << debugIndices[i] << std::endl;
            }
        }
        
        glGenVertexArraysOES(1, &m_debugVAO);
        glBindVertexArrayOES(m_debugVAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexStride * numVertices, vertexBuffer, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(VTXATTRIB_POSITION);
        glVertexAttribPointer(VTXATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(VTXATTRIB_NORMAL);
        glVertexAttribPointer(VTXATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)(sizeof(float) * 3));

        glGenBuffers(1, &m_debugIndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_debugIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_numDebugIndices, debugIndices, GL_STATIC_DRAW);
        
        delete [] debugIndices;
    }
#endif
    
    glBindVertexArrayOES(0);    
}

