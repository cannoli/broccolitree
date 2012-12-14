//
//  ModelLib.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "ModelLib.h"
#include "Shape.h"
#include <iostream>
#include <assert.h>

//
// singleton
//
ModelLib* ModelLib::singleton = NULL;

void ModelLib::DestroyInstance()
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
ModelLib::ModelLib(unsigned int capacity)
: m_capacity(capacity)
, m_numShapes(0)
{
    m_shapesReg = new Shape* [capacity];
}

ModelLib::~ModelLib()
{
    for(unsigned int i = 0; i < m_numShapes; ++i)
    {
        delete m_shapesReg[i];
    }
    delete [] m_shapesReg;
}


//
// load
//
void ModelLib::AddShape(Shape *newShape)
{
    assert(m_numShapes < m_capacity);
    if(m_numShapes < m_capacity)
    {
        m_shapesReg[m_numShapes] = newShape;
        ++m_numShapes;
    }
}

Shape* ModelLib::GetShape(unsigned int shapeId)
{
    Shape* result = NULL;
    assert(m_numShapes > shapeId);
    if(m_numShapes > shapeId)
    {
        result = m_shapesReg[shapeId];
    }
    return result;
}