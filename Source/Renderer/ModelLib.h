//
//  ModelLib.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/7/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_ModelLib_h
#define broc_ModelLib_h

class Shape;

class ModelLib
{
public:
    static inline ModelLib* CreateInstance(unsigned int capacity)
    {
        if(!singleton)
        {
            singleton = new ModelLib(capacity);
        }
        return singleton;
    }
    static inline ModelLib* GetInstance()
    {
        if(!singleton)
        {
            singleton = new ModelLib;
        }
        return singleton;
    }
    static void DestroyInstance();
    virtual ~ModelLib();
    
    // load
    void AddShape(Shape* newShape);
    
    // accessors
    Shape* GetShape(unsigned int shapeId);
    
protected:
    unsigned int m_capacity;
    unsigned int m_numShapes;
    Shape** m_shapesReg;
    
private:
    static ModelLib* singleton;
    ModelLib(unsigned int capacity = 10);
};


#endif
