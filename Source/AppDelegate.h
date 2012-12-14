//
//  AppDelegate.h
//  broc
//
//  Created by Shu Chiun Cheah on 3/28/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//


#import <UIKit/UIKit.h>

@class StartScreen;

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UINavigationController *_navController;	
}
@property (strong, nonatomic) UIWindow *window;
@property (nonatomic,retain) UINavigationController *navController;
@property (strong, nonatomic) StartScreen *rootController;

@end