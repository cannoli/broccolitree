//
//  FileResource.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/12/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_FileResource_h
#define broc_FileResource_h

class FileResourceImpl;
class FileResource
{
public:
    FileResource(const char* filename);
    ~FileResource();
    
    const char* GetContentAsUTF8String();
    
protected:
    FileResourceImpl* m_impl;
};

#endif
