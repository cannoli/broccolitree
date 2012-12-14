//
//  FileResourceObjC.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/12/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FileResourceObjC : NSObject

- (id) initWithFileNamed:(NSString*)filename;
- (const char*) getContentAsUTF8String;

@end
