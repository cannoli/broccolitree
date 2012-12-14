//
//  RenderBucket.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "RenderBucket.h"
#include "RenderCmd.h"
#include "GLKMath.h"
#include <iostream>
#include <assert.h>

//
// constructor/destructor
//
RenderBucket::RenderBucket(unsigned int maxEntries)
: m_maxEntries(maxEntries)
, m_nextEntry(0)
, m_bucketMatrix(GLKMatrix4Identity)
{
    m_entries = new RenderCmd*[maxEntries];
}

RenderBucket::~RenderBucket()
{
    delete [] m_entries;
}

//
// Draw
//
void RenderBucket::Execute()
{
    for(unsigned int i = 0; i < m_nextEntry; ++i)
    {
        m_entries[i]->Execute();
    }
}

void RenderBucket::AddCmd(RenderCmd *newCmd)
{
    unsigned int next = m_nextEntry;
    assert(next < m_maxEntries);
    if(next < m_maxEntries)
    {
        m_entries[next] = newCmd;
        next++;
    }
    m_nextEntry = next;
}

void RenderBucket::Reset()
{
    m_nextEntry = 0;
}

void RenderBucket::SetBucketMatrix(const GLKMatrix4 &matrix)
{
    m_bucketMatrix = matrix;
}