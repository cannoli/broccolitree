//
//  FileResourceObjCInterface.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/12/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_FileResourceObjCInterface_h
#define broc_FileResourceObjCInterface_h


class FileResourceImpl
{
public:
    FileResourceImpl();
    ~FileResourceImpl();
    
    void Init(const char* filename);
    const char* GetContentAsUTF8String();
    
protected:
    void* self;
};


#endif
