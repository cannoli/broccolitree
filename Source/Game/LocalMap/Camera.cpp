//
//  Camera.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 3/14/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "Camera.h"
#include "Vec3.h"
#include "GLKMath.h"
#include "GameRenderer.h"
#include "Renderer.h"
#include "RenderCmdFactory.h"
#include <math.h>
#include <iostream>
#include <stdio.h>

// constructor/destructor
Camera::Camera(float pitch, float yaw, float distance)
{
    // the camera is y-up; so, it's zero-pitch is pointing down (into negative z)
    // the game world zero-pitch is in positive y direction
    // so, we need to add an additional 90 degrees
    mCamRotX = pitch + M_PI_2;
    mCamRotZ = yaw;
    m_focusDistance = distance;
    
    // adjust camera position to look at origin from a distance
    mPos = new Vec3(0.0f, 0.0f, 0.0f);
    SetFocusPoint(Vec3(0.0f, 0.0f, 0.0f), distance);

    GLKMatrix4 transform = ViewToWorldMatrix();
    
    // setup motion basis vectors
    mUp = new Vec3(0.0f, 1.0f, 0.0f);
    mForward = new Vec3(0.0f, 0.0f, -1.0f);
    mVecSide = GLKVector3Make(1.0f, 0.0f, 0.0f);
    mVecForward = GLKVector3Make(0.0f, 0.0f, -1.0f);
    mVecSide = GLKMatrix4MultiplyVector3(transform, mVecSide);
    mVecSide.z = 0.0f;
    mVecSide = GLKVector3Normalize(mVecSide);
    mVecForward = GLKMatrix4MultiplyVector3(transform, mVecForward);
    mVecForward.z = 0.0f;
    mVecForward = GLKVector3Normalize(mVecForward);
    
    // default to perspective projection
    m_camType = CAMTYPE_PERSPECTIVE;
}

Camera::~Camera()
{
    delete mForward;
    delete mPos;
    delete mUp;
}

// properties
void Camera::SetPerspectiveParams(float fovyRadians, float aspectRatio, float nearZ, float farZ)
{
    // store params
    m_fovyRadians = fovyRadians;
    m_aspect = aspectRatio;
    m_orthoAspectScale = 1.0f;
    m_nearZ = nearZ;
    m_farZ = farZ;
    m_camType = CAMTYPE_PERSPECTIVE;
    
    // compute and store projection matrix
    m_projectionMatrix = GLKMatrix4MakePerspective(m_fovyRadians, m_aspect, m_nearZ, m_farZ);
}

void Camera::SetOrthoParams(float aspectScale, float aspectRatio, float nearZ, float farZ)
{
    // store params
    m_fovyRadians = M_PI_2;
    m_aspect = aspectRatio;
    m_orthoAspectScale = aspectScale;
    m_nearZ = nearZ;
    m_farZ = farZ;
    m_camType = CAMTYPE_ORTHO;
    
    // compute and store projection matrix
    float halfWidth = aspectScale * aspectRatio;
    float halfHeight = aspectScale;
    m_projectionMatrix = GLKMatrix4MakeOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearZ, farZ);
}

//
// target properties
//
void Camera::SetFocusPoint(const Vec3 &target, float distance)
{
    m_focusPoint = target;
    
    // compute camera position as the point at the given distance away along the 3D forward vector of the camera
    GLKVector3 viewForward = GLKVector3Make(0.0f, 0.0f, -1.0f);
    GLKVector3 targetToCam = GLKMatrix4MultiplyVector3(ViewToWorldMatrix(), viewForward);
    GLKVector3 targetToCamUnit = GLKVector3Normalize(targetToCam);
    GLKVector3 camPos = GLKVector3Add(m_focusPoint.AsGLKVector3(), GLKVector3MultiplyScalar(targetToCamUnit, -distance));
        
    mPos->Set(camPos.x, camPos.y, camPos.z);
}

void Camera::IncrRotX(float radians)
{
    mCamRotX += radians;
}

void Camera::IncrRotZ(float radians)
{
    mCamRotZ += radians;

    GLKMatrix4 transform = ViewToWorldMatrix();
    mVecSide = GLKVector3Make(1.0f, 0.0f, 0.0f);
    mVecForward = GLKVector3Make(0.0f, 0.0f, -1.0f);
    mVecSide = GLKMatrix4MultiplyVector3(transform, mVecSide);
    mVecSide.z = 0.0f;
    mVecSide = GLKVector3Normalize(mVecSide);
    mVecForward = GLKMatrix4MultiplyVector3(transform, mVecForward);
    mVecForward.z = 0.0f;
    mVecForward = GLKVector3Normalize(mVecForward);
}

void Camera::MovePlanar(float incrX, float incrY)
{
    GLKVector3 side = GLKVector3MultiplyScalar(mVecSide, incrX);
    (*mPos)+= side;
    GLKVector3 forward = GLKVector3MultiplyScalar(mVecForward, incrY);
    (*mPos)+= forward;
}


// matrices

GLKMatrix4 Camera::ViewMatrix() const
{
    // reverse all rotations to construct view rotation transform
    GLKQuaternion rotX = GLKQuaternionMakeWithAngleAndAxis(-mCamRotX, 1.0f, 0.0f, 0.0f);
    GLKQuaternion rotY = GLKQuaternionMakeWithAngleAndAxis(-mCamRotZ, 0.0f, 0.0f, 1.0f);
    GLKQuaternion viewRot = GLKQuaternionMultiply(rotX, rotY);
    GLKMatrix4 result = GLKMatrix4MakeWithQuaternion(viewRot);
    
    // reverse the position
    GLKVector3 pos = GLKVector3MultiplyScalar(mPos->AsGLKVector3(), -1.0f);
    GLKMatrix4 trans = GLKMatrix4MakeTranslation(pos.x, pos.y, pos.z);
    result = GLKMatrix4Multiply(result, trans);
    return(result);
}

GLKMatrix4 Camera::ViewProjectionMatrix() const
{
    GLKMatrix4 view = this->ViewMatrix();
    GLKMatrix4 result = GLKMatrix4Multiply(m_projectionMatrix, view);
    return result;
}

GLKMatrix4 Camera::ViewToWorldMatrix() const
{
    GLKQuaternion rotX = GLKQuaternionMakeWithAngleAndAxis(mCamRotX, 1.0f, 0.0f, 0.0f);
    GLKQuaternion rotY = GLKQuaternionMakeWithAngleAndAxis(mCamRotZ, 0.0f, 0.0f, 1.0f);
    GLKQuaternion viewRot = GLKQuaternionMultiply(rotY, rotX);
    GLKMatrix4 result = GLKMatrix4MakeWithQuaternion(viewRot);
    GLKVector3 pos = mPos->AsGLKVector3();
    result = GLKMatrix4Translate(result, pos.x, pos.y, pos.z);
    return result;
}


//
// debug
//
void Camera::print()
{
#if defined(DEBUG)    
    printf("View Matrix:\n");
    PrintGLKMatrix4(this->ViewMatrix());
    printf("\n");
#endif
}

// utility functions
void Camera::PrintGLKMatrix4(const GLKMatrix4& mtx)
{
#if defined(DEBUG)
    printf("| %.3f\t%.3f\t%.3f\t%.3f |\n", mtx.m00, mtx.m10, mtx.m20, mtx.m30);
    printf("| %.3f\t%.3f\t%.3f\t%.3f |\n", mtx.m01, mtx.m11, mtx.m21, mtx.m31);
    printf("| %.3f\t%.3f\t%.3f\t%.3f |\n", mtx.m02, mtx.m12, mtx.m22, mtx.m32);
    printf("| %.3f\t%.3f\t%.3f\t%.3f |\n", mtx.m03, mtx.m13, mtx.m23, mtx.m33);
#endif
}
