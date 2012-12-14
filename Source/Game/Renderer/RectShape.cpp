//
//  RectShape.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//


#include "RectShape.h"
#include "Renderer.h"
#include "GameRenderer.h"
#include "RenderCmdFactory.h"
#include "SimpleMaterialCmd.h"
#include "VertexAttributes.h"
#include <iostream>

static const unsigned int NUMVERTS = 4;
static GLfloat sRectVertexData[NUMVERTS * 6] =
{
     0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};
static GLushort sRectIndexData[NUMVERTS] =
{
    0, 1, 2, 3
};

//
// construct/destructor
//
RectShape::RectShape()
: Shape(sRectVertexData, 6 * sizeof(GLfloat), NUMVERTS,
        sRectIndexData, sizeof(GLushort), NUMVERTS, false)
{
#if defined(DEBUG)
    // init debug lines for TRIANGLE_FAN
    {
        glBindVertexArrayOES(0);    
        
        unsigned int vertexStride = 6 * sizeof(GLfloat);
        GLfloat* vertexBuffer = sRectVertexData;
        unsigned int numIndices = NUMVERTS;
        m_numDebugIndices = NUMVERTS * 2;
        GLushort* indexBuffer = sRectIndexData;
        GLushort* debugIndices = new GLushort[m_numDebugIndices];
        unsigned int cur = 0;
        unsigned int debugIndex = 0;
        while(cur < numIndices)
        {
            assert((debugIndex + 1) < m_numDebugIndices);
            unsigned int next = cur + 1;
            if(next >= numIndices)
            {
                next = 0;
            }
            
            // edge 1
            debugIndices[debugIndex] = indexBuffer[cur];
            debugIndices[debugIndex+1] = indexBuffer[next];
            
            debugIndex += 2;
            cur++;
        }
        /*
        {
            for(unsigned int i = 0; i < m_numDebugIndices; ++i)
            {
                std::cout << debugIndices[i] << std::endl;
            }
        }
        */
        glGenVertexArraysOES(1, &m_debugVAO);
        glBindVertexArrayOES(m_debugVAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexStride * NUMVERTS, vertexBuffer, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(VTXATTRIB_POSITION);
        glVertexAttribPointer(VTXATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(VTXATTRIB_NORMAL);
        glVertexAttribPointer(VTXATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)(sizeof(float) * 3));
        
        glGenBuffers(1, &m_debugIndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_debugIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_numDebugIndices, debugIndices, GL_STATIC_DRAW);
        
        glBindVertexArrayOES(0);
        delete [] debugIndices;
    }
#endif

}

RectShape::~RectShape()
{
    
}

