//
//  GLViewController.h
//  broc
//
//  Created by Shu Chiun Cheah on 3/13/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GLViewController : UIViewController
{    
    BOOL _isRotating;
    IBOutlet UIButton *_buttonTransformToggle;
    IBOutlet UIButton *_buttonCamToggle;
}
- (IBAction)toggleTransform:(id)sender;
- (IBAction)toggleCamType:(id)sender;
@end
