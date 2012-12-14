//
//  StartScreen.m
//  broc
//
//  Created by Shu Chiun Cheah on 4/13/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import "StartScreen.h"
#import "GLViewController.h"
#import "AppDelegate.h"

@interface StartScreen ()
@end

@implementation StartScreen

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
    {
    }
    return self;
}

- (void) dealloc
{
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


#pragma mark - button actions

- (IBAction)localMapPressed:(id)sender 
{
    GLViewController* localMap = [[GLViewController alloc] initWithNibName:@"GLViewController" bundle:nil];
    AppDelegate* appDelegate = [[UIApplication sharedApplication] delegate];
    [appDelegate.navController pushViewController:localMap animated:YES];
    [localMap release];
}

@end
