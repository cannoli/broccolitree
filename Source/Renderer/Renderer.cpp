//
//  Renderer.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "Renderer.h"
#include "RenderBucket.h"
#include "RenderContext.h"
#include <iostream>
#include <assert.h>

static const unsigned int RENDERER_MATRIXSTACKSIZE = 20;
static const unsigned int RENDERER_MAXSHADERUNIFORMS = 20;

//
// singleton
//
Renderer* Renderer::singleton = NULL;
void Renderer::DestroyInstance()
{
    if(singleton)
    {
        delete singleton;
    }
    singleton = NULL;
}

// constructor/destructor
Renderer::Renderer(unsigned int numBuckets, unsigned int numBuffers)
: m_numBuckets(numBuckets)
, m_numBuffers(numBuffers)
, m_curBuffer(0)
{
    m_renderBuckets = new RenderBucket**[numBuffers];
    for(unsigned int buffer = 0; buffer < numBuffers; ++buffer)
    {
        m_renderBuckets[buffer] = new RenderBucket*[numBuckets];
        for(unsigned int bucket = 0; bucket < numBuckets; ++bucket)
        {
            m_renderBuckets[buffer][bucket] = NULL;
        }
    }
    m_renderContext = new RenderContext(RENDERER_MATRIXSTACKSIZE, RENDERER_MAXSHADERUNIFORMS);
}

Renderer::~Renderer()
{
    delete m_renderContext;
    for(unsigned int buffer = 0; buffer < m_numBuffers; ++buffer)
    {
        for(unsigned int bucket = 0; bucket < m_numBuckets; ++bucket)
        {
            if(m_renderBuckets[buffer][bucket])
            {
                delete [] m_renderBuckets[buffer][bucket];
            }
        }
        delete [] m_renderBuckets[buffer];
    }
    delete [] m_renderBuckets;
}

//
// init functions
//
void Renderer::InitRenderBucket(unsigned int bucketId, unsigned int maxEntries)
{
    if(m_numBuckets > bucketId)
    {
        for(unsigned int buffer = 0; buffer < m_numBuffers; ++buffer)
        {
            m_renderBuckets[buffer][bucketId] = new RenderBucket(maxEntries);
        }
    }
}

//
// rendering
//
void Renderer::SetBucketMatrix(unsigned int bucketId, const GLKMatrix4& matrix)
{
    assert(m_numBuckets > bucketId);
    RenderBucket* cur = m_renderBuckets[m_curBuffer][bucketId];
    cur->SetBucketMatrix(matrix);
}

void Renderer::AddCmd(unsigned int bucketId, RenderCmd *cmd)
{
    assert(m_numBuckets > bucketId);
    RenderBucket* cur = m_renderBuckets[m_curBuffer][bucketId];
    cur->AddCmd(cmd);
}

void Renderer::Submit()
{
    RenderBucket** curList = m_renderBuckets[m_curBuffer];
    for(unsigned int i = 0; i < m_numBuckets; ++i)
    {
        RenderBucket* curBucket = curList[i];
        m_renderContext->PushMatrix(curBucket->m_bucketMatrix);
        curBucket->Execute();
        m_renderContext->PopMatrix();
    }
    
    // done submitting to GL, reset all buckets prior to flip
    for(unsigned int i = 0; i < m_numBuckets; ++i)
    {
        RenderBucket* curBucket = curList[i];
        curBucket->Reset();
    }
    
    m_curBuffer++;
    if(m_numBuffers <= m_curBuffer)
    {
        m_curBuffer = 0;
    }
}