//
//  FileResource.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/12/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "FileResource.h"
#include "FileResourceObjCInterface.h"
#include <iostream>

//
// constructor/destructor
//
FileResource::FileResource(const char* filename)
{
    m_impl = new FileResourceImpl;
    m_impl->Init(filename);
}

FileResource::~FileResource()
{
    delete m_impl;
}


//
// accessors
//
const char* FileResource::GetContentAsUTF8String()
{
    return m_impl->GetContentAsUTF8String();
}
