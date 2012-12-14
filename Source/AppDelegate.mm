//
//  AppDelegate.m
//  broc
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import "AppDelegate.h"
#import "StartScreen.h"

static const NSTimeInterval kAppSessionExpiry = 12.0 * 60.0 * 60.0;   // seconds

@interface AppDelegate()
@end

@implementation AppDelegate
@synthesize window = _window;
@synthesize rootController = _rootController;
@synthesize navController = _navController;

- (void)dealloc
{
    [self teardownNavigationController];
    [_window release];
    [super dealloc];
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application 
{
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{    
    // hide the status bar
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
    
    // create window
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    [self.window setBackgroundColor:[UIColor whiteColor]];
    [self.window makeKeyAndVisible];
    
    // setup navigation controller
    [self setupNavigationController];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
}

- (void)applicationWillTerminate:(UIApplication *)application
{
}

#pragma mark - UI
- (void) setupNavigationController
{
    // create the root view controller first
    self.rootController = [[[StartScreen alloc] initWithNibName:@"StartScreen" bundle:nil] autorelease];
    
    // add it to our navigation controller
    self.navController = [[[UINavigationController alloc] initWithRootViewController:[self rootController]] autorelease];
    [self.navController setNavigationBarHidden:YES];
    [self.window addSubview:[[self navController]view]];
}

- (void) teardownNavigationController
{
    [self.navController.view removeFromSuperview];
    self.rootController = nil;
    self.navController = nil;
}


@end
