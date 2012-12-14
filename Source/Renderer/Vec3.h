//
//  Vec3.h
//  broc
//
//  Created by Shu Chiun Cheah on 3/14/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_Vec3_h
#define broc_Vec3_h

#include "GLKMathTypes.h"

class Vec4;
class Vec3
{
public:
    float v[4];

    Vec3();
    Vec3(float x, float y, float z);
    Vec3(const float vec[3]);
    ~Vec3();
    
    float Magnitude() const;
    float operator[](unsigned int index) const;
    void operator=(const Vec3& v1);
    void operator+=(GLKVector3 v2);
    void Set(float x, float y, float z);
    inline float GetX()
    {
        return v[0];
    }
    inline float GetY()
    {
        return v[1];
    }
    inline float GetZ()
    {
        return v[2];
    }
    
    GLKVector3 AsGLKVector3();
    
    void print();
    
    // vector operations
    friend Vec3 CrossProduct(const Vec3& v1, const Vec3& v2);
    friend Vec3 operator-(const Vec3& v1, const Vec3& v2);
    friend Vec3 operator+(const Vec3& v1, const Vec3& v2);
    friend Vec3 Normalize(const Vec3& v1);
    friend Vec3 operator*(const float scalar, const Vec3& v1);
    
    // friend classes
    friend class Matrix44;
    friend class Vec4;
};

#endif
