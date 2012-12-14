//
//  MenuImageManager.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/26/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MenuImageManager : NSObject
{
}

// frontend menu
- (void) loadFrontMenuBackground;       // ok to call this repeatedly
- (void) unloadFrontMenuBackground;

// singleton
+(MenuImageManager*) getInstance;
+(void) destroyInstance;

@end
