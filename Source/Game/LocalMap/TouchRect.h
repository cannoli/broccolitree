//
//  TouchRect.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/10/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_TouchRect_h
#define broc_TouchRect_h

#include "IRenderComponent.h"
#include "GLKMathTypes.h"
#include <stdlib.h>

class Shape;

class TouchRect : public IRenderComponent
{
public:
    TouchRect();
    ~TouchRect();
    
    // Placement new operator
    //void* operator new (size_t sz, void* object)
    //{
    //    return object;
   // }

    // properties
    void SetRect(float centerX, float centerY, float width, float height, float z);
    inline GLKVector2 GetOrigin() const
    {
        return m_origin;
    }
    inline GLKVector2 GetSize() const
    {
        return m_size;
    }
    inline float GetZDist() const
    {
        return m_zDist;
    }
    
    // touch test
    bool DoesContainPoint(float pointX, float pointY) const;
    
    // render component
    virtual void InitRenderComponent();
    virtual void ShutdownRenderComponent();
    virtual void AddDraw();
    
protected:
    Shape*      m_model;
    GLKVector2  m_origin;
    GLKVector2  m_size;
    float       m_zDist;
};

#endif
