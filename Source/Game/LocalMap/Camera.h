//
//  Camera.h
//  broc
//
//  Created by Shu Chiun Cheah on 3/14/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_Camera_h
#define broc_Camera_h
#include "GLKMathTypes.h"
#include "Vec3.h"
#include <math.h>

enum _CameraType
{
    CAMTYPE_PERSPECTIVE = 0,
    CAMTYPE_ORTHO,
    
    CAMTYPE_NUM
};

class Camera
{
private:
    
    // runtime controls
    float mCamRotX;
    float mCamRotZ;
    GLKVector3 mVecSide;
    GLKVector3 mVecForward;
    
    // camera config params
    float m_fovyRadians;
    float m_aspect;
    float m_orthoAspectScale;
    float m_nearZ;
    float m_farZ;
    unsigned int m_camType;
    Vec3 m_focusPoint;
    float m_focusDistance;
    
    GLKMatrix4 m_projectionMatrix;
    Vec3* mPos;
    Vec3* mUp;
    Vec3* mForward;
    
    
protected:
    
public:
    Camera(float pitch = -0.35f * M_PI_2, float yaw = 0.1f * M_PI_2, float distance = 10.0f);
    virtual ~Camera();
    
    // properties
    void SetPerspectiveParams(float fovyRadians, float aspectRatio, float nearZ, float farZ);
    void SetOrthoParams(float aspectScale, float aspectRatio, float nearZ, float farZ);
    
    // target properties
    void SetFocusPoint(const Vec3& target, float distance);    
    
    // movements
    void IncrRotX(float radians);
    void IncrRotZ(float radians);
    void MovePlanar(float incrX, float incrY);
    
    // matrices
    GLKMatrix4 ViewMatrix() const;
    GLKMatrix4 ViewProjectionMatrix() const;
    GLKMatrix4 ViewToWorldMatrix() const;
    
    // debug
    void print();
    static void PrintGLKMatrix4(const GLKMatrix4& mtx);
};


#endif
