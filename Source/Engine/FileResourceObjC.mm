//
//  FileResourceObjC.m
//  broc
//
//  Created by Shu Chiun Cheah on 4/12/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import "FileResourceObjC.h"
#import "FileResourceObjCInterface.h"

@interface FileResourceObjC()
{
    NSString* _fileText;
}
@end

@implementation FileResourceObjC

- (id) initWithFileNamed:(NSString *)filename
{
    self = [super init];
    if(self)
    {
        NSArray* components = [filename componentsSeparatedByString:@"."];
        NSString* fileRoot = [components objectAtIndex:0];
        NSString* fileExt = @".brc";
        if(1 < [components count])
        {
            fileExt = [components objectAtIndex:1];
        }
        NSString* path = [[NSBundle mainBundle] pathForResource:fileRoot ofType:fileExt];
        _fileText = [[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil] retain];
    }
    return self;
}

- (void) dealloc
{
    [_fileText release];
    [super dealloc];
}

- (const char*) getContentAsUTF8String
{
    return [_fileText UTF8String];
}

//
// C++ wrapper
//

FileResourceImpl::FileResourceImpl()
: self(NULL)
{
    
}

FileResourceImpl::~FileResourceImpl()
{
    [(id)self dealloc];
}

void FileResourceImpl::Init(const char *filename)
{
    self = [[FileResourceObjC alloc] initWithFileNamed:[NSString stringWithCString:filename encoding:NSASCIIStringEncoding]];
}

const char* FileResourceImpl::GetContentAsUTF8String()
{
    return [(id)self getContentAsUTF8String];
}


@end

