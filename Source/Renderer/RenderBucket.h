//
//  RenderBucket.h
//  broc
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_RenderBucket_h
#define broc_RenderBucket_h

#include "GLKMathTypes.h"

class Renderer;
class RenderCmd;

class RenderBucket
{
public:
    RenderBucket(unsigned int maxEntries);
    virtual ~RenderBucket();
    
    void Execute();
    void AddCmd(RenderCmd* newCmd);
    void Reset();
    
    // properties
    void SetBucketMatrix(const GLKMatrix4& matrix);
    
protected:
    unsigned int m_maxEntries;
    RenderCmd**  m_entries;
    unsigned int m_nextEntry;
    
    GLKMatrix4   m_bucketMatrix;    // this matrix gets pushed at the beginning of each bucket
                                    // typically, you want to use this for the viewProj matrix
    friend class Renderer;
};

#endif
