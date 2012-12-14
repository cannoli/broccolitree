//
//  MenuImageManager.m
//  broc
//
//  Created by Shu Chiun Cheah on 4/26/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import "MenuImageManager.h"
#import "AppDelegate.h"

@interface MenuImageManager ()
{
    UIView* _frontMenuBgView;
}
@property (nonatomic,retain) UIView* frontMenuBgView;
@end

@implementation MenuImageManager
@synthesize frontMenuBgView = _frontMenuBgView;

- (id) init
{
    self = [super init];
    if(self)
    {
        _frontMenuBgView = nil;
    }
    return self;
}

- (void) dealloc
{
    [_frontMenuBgView release];
    [super dealloc];
}

#pragma mark - frontend menu
- (void) loadFrontMenuBackground
{
    if(![self frontMenuBgView])
    {
        AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
        NSString* backgroundImageName = @"Default.png";
        if([[UIScreen mainScreen] scale] > 1.0f)
        {
            backgroundImageName = @"Default@2x.png";
        }
        UIImage* backgroundImage = [UIImage imageNamed:backgroundImageName];
        UIImageView* imageView = [[[UIImageView alloc] initWithFrame:delegate.window.bounds] autorelease];
        imageView.image = backgroundImage;
        [delegate.window addSubview:imageView];
        [delegate.window sendSubviewToBack:imageView];
        self.frontMenuBgView = imageView;
    }
}

- (void) unloadFrontMenuBackground
{
    if([self frontMenuBgView])
    {
        [self.frontMenuBgView removeFromSuperview];
        self.frontMenuBgView = nil;
    }
}


#pragma mark - Singleton
static MenuImageManager* singleton = nil;
+ (MenuImageManager*) getInstance
{
	@synchronized(self)
	{
		if (!singleton)
		{
			singleton = [[[MenuImageManager alloc] init] retain];
		}
	}
	return singleton;
}

+ (void) destroyInstance
{
	@synchronized(self)
	{
		[singleton release];
		singleton = nil;
	}
}

@end
