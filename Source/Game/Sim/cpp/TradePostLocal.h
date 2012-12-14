//
//  TradePostLocal.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_TradePostLocal_h
#define broc_TradePostLocal_h

#include "IRenderComponent.h"
#include "GLKMathTypes.h"
#include "Vec3.h"
#include <stdlib.h>

class Shape;
class TouchRect;

class TradePostLocal : public IRenderComponent
{
public:
    TradePostLocal();
    TradePostLocal(float x, float y, float z);
    ~TradePostLocal();
    
    // Placement new operator
    void* operator new (size_t sz, void* object); 

    // properties
    const TouchRect* RefreshTouchRect(GLKMatrix4 viewProjMatrix);
    inline const TouchRect* GetTouchRect()
    {
        return m_touchRect;
    }
    inline void SetPos(const Vec3& pos)
    {
        m_pos = pos;
    }
    inline Vec3 GetPos() const
    {
        return m_pos;
    }
    inline void SetName(const char* name)
    {
        m_name = name;
    }
    inline const char* GetName() const
    {
        return m_name;
    }
    
    // render component
    virtual void InitRenderComponent();
    virtual void ShutdownRenderComponent();
    virtual void AddDraw();
    
protected:
    const char* m_name;
    Shape*      m_model;
    Vec3        m_pos;
    GLKMatrix4  m_transform;
    
    // 2D rect to detect user touches
    TouchRect*  m_touchRect;
    
private:
};

#endif
