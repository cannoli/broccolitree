//
//  Vec3.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 3/14/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "Vec3.h"
#include "GLKMath.h"
#include <math.h>
#include <stdio.h>

// constructor/destructor

Vec3::Vec3()
{
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
}

Vec3::Vec3(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
}

Vec3::Vec3(const float vec[3])
{
    v[0] = vec[0];
    v[1] = vec[1];
    v[2] = vec[2];
    v[3] = 0.0f;
}

Vec3::~Vec3()
{
    
}

float Vec3::Magnitude() const
{
    float result = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
    result = sqrtf(result);
    return result;
}

float Vec3::operator[](unsigned int index) const
{
    float result = 0.0f;
    if(3 > index)
    {
        result = v[index];
    }
    return result;
}

void Vec3::operator=(const Vec3& v1)
{
    v[0] = v1.v[0];
    v[1] = v1.v[1];
    v[2] = v1.v[2];
    v[3] = v1.v[3];
}

void Vec3::operator+=(GLKVector3 v2)
{
    v[0] += v2.x;
    v[1] += v2.y;
    v[2] += v2.z;
}

void Vec3::Set(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

GLKVector3 Vec3::AsGLKVector3()
{
    GLKVector3 result = GLKVector3Make(v[0], v[1], v[2]);
    return result;
}

void Vec3::print()
{
#if defined(DEBUG)
    printf("(%.3f, %.3f, %.3f)\n", v[0], v[1], v[2]);
#endif
}
// vector operations
Vec3 CrossProduct(const Vec3& v1, const Vec3& v2)
{
    Vec3 result;
    result.v[0] = (v1.v[1] * v2.v[2]) - (v2.v[1] * v1.v[2]);
    result.v[1] = (v2.v[0] * v1.v[2]) - (v1.v[0] * v2.v[2]);
    result.v[2] = (v1.v[0] * v2.v[1]) - (v2.v[0] * v1.v[1]);
    
    return result;
}

Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    Vec3 result;
    result.v[0] = v1.v[0] - v2.v[0];
    result.v[1] = v1.v[1] - v2.v[1];
    result.v[2] = v1.v[2] - v2.v[2];
    
    return result;
}

Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    Vec3 result;
    result.v[0] = v1.v[0] + v2.v[0];
    result.v[1] = v1.v[1] + v2.v[1];
    result.v[2] = v1.v[2] + v2.v[2];
    
    return result;
}

Vec3 Normalize(const Vec3& v1)
{
    Vec3 result;
    float mag = v1.Magnitude();
    
    result.v[0] = v1.v[0] / mag;
    result.v[1] = v1.v[1] / mag;
    result.v[2] = v1.v[2] / mag;
    
    return result;
}

Vec3 operator*(const float scalar, const Vec3& v1)
{
    Vec3 result(scalar * v1.v[0], scalar * v1.v[1], scalar * v1.v[2]);
    return result;
}

