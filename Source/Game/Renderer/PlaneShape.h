//
//  PlaneShape.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_PlaneShape_h
#define broc_PlaneShape_h

#include "Shape.h"

class PlaneShape : public Shape
{
public:
    PlaneShape(float width, float length, unsigned int numWidthDiv, unsigned int numLengthDiv);
    virtual ~PlaneShape();
};


#endif
