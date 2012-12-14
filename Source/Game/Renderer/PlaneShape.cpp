//
//  PlaneShape.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//


#include "PlaneShape.h"
#include "Renderer.h"
#include "GameRenderer.h"
#include "RenderCmdFactory.h"
#include "SimpleMaterialCmd.h"
#include <iostream>

static const unsigned int POS_NUMELEMENTS = 3;
static const unsigned int NORMAL_NUMELEMENTS = 3;

#if defined(DEBUG)
static bool sDebugPlaneShapeVerbose = false;
#endif

//
// construct/destructor
//
PlaneShape::PlaneShape(float width, float length, unsigned int numWidthDiv, unsigned int numLengthDiv)
: Shape()
{
    float beginX = -0.5f * width;
    float beginY = -0.5f * length;
    float incrX = width / static_cast<float>(numWidthDiv);
    float incrY = length / static_cast<float>(numLengthDiv);
    unsigned int numVerts = (numWidthDiv+1) * (numLengthDiv+1);
    GLfloat* verts = new GLfloat[numVerts * (POS_NUMELEMENTS + NORMAL_NUMELEMENTS)];
    GLfloat* vert = &(verts[0]);
    float curX = beginX;
    for(unsigned int xStep = 0; xStep <= numWidthDiv; ++xStep)
    {
        float curY = beginY;
        for(unsigned int yStep = 0; yStep <= numLengthDiv; ++yStep)
        {
            vert[0] = curX;
            vert[1] = curY;
            vert[2] = 0.0f;
            vert[3] = 0.0f;
            vert[4] = 0.0f;
            vert[5] = 1.0f;
            
            curY += incrY;
            vert += (POS_NUMELEMENTS + NORMAL_NUMELEMENTS);
        }
        curX += incrX;
    }
    
#if defined(DEBUG)
    if(sDebugPlaneShapeVerbose)
    {
        unsigned int debugIndex = 0;
        for(unsigned int i = 0; i < numVerts; ++i)
        {
            std::cout << verts[debugIndex] << "," << verts[debugIndex+1] << "," << verts[debugIndex+2] << "; " <<
            verts[debugIndex+3] << "," << verts[debugIndex+4] << "," << verts[debugIndex+5] << std::endl;
            
            debugIndex += 6;
        }
    }
#endif
    
    unsigned int numTiles = numWidthDiv * numLengthDiv;
    unsigned int indicesPerTile = 2 * 3;    // 2 tris, each has 3 vertices;
    unsigned int numIndices = numTiles * indicesPerTile;
    GLushort* indices = new GLushort[numIndices];
    GLushort* curIndex = &(indices[0]);
    for(unsigned int col = 0; col < numWidthDiv; ++col)
    {
        unsigned int leftIndex = col * (numLengthDiv+1);
        unsigned int rightIndex = leftIndex + (numLengthDiv+1);
        for(unsigned int row = 0; row < numLengthDiv; ++row)
        {
            // left tri
            curIndex[0] = leftIndex;
            curIndex[1] = rightIndex;
            curIndex[2] = leftIndex+1;
            
            // right tri
            curIndex[3] = rightIndex;
            curIndex[4] = rightIndex+1;
            curIndex[5] = leftIndex+1;
            
            leftIndex++;
            rightIndex++;
            curIndex += indicesPerTile;
        }
    }
    
#if defined(DEBUG)
    if(sDebugPlaneShapeVerbose)
    {
        for(unsigned int i = 0; i < numIndices; ++i)
        {
            std::cout << indices[i] << std::endl;
        }
    }
#endif
    
    this->CreateBuffers(verts, sizeof(GLfloat) * (POS_NUMELEMENTS+NORMAL_NUMELEMENTS), numVerts, 
                        indices, sizeof(GLushort), numIndices, true);
    delete [] verts;
    delete [] indices;
}

PlaneShape::~PlaneShape()
{
    
}

