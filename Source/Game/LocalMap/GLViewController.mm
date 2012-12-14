//
//  GLViewController.m
//  broc
//
//  Created by Shu Chiun Cheah on 3/13/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#import "GLViewController.h"
#import "RendererGLView.h"
#import "AppDelegate.h"
#import <GLKit/GLKit.h>
#import <QuartzCore/QuartzCore.h>
#include "Camera.h"
#include "GameRenderer.h"
#include "GameManager.h"
#include "TradePostLocal.h"


static const float kCameraFov = 65.0f * M_PI / 180.0f;  // 65 degrees in radians
static const float kCameraOrthoAspectScale = 10.0f;
static const float kCameraNearZ = 0.1f;
static const float kCameraFarZ = 500.0f;
static const NSInteger kFrameInterval = 1;
static const CFTimeInterval kMaxFrametime = 1.0 / 20.0;

@interface GLViewController ()
{
    RendererGLView* _glView;    // renderer GL view retained to make calls directly to it
    
    // display link
    CADisplayLink* _displayLink;
    BOOL _displayTickActive;
    CFTimeInterval _previousTime;  
    
    UITouch* _panTouch;
    UITouch* _panTouch2;
    CGPoint _prevPoint;
    CGPoint _curPoint;
    CGPoint _prevPoint2;
    CGPoint _curPoint2;
    BOOL _isTwoFingerTranslation;
    BOOL _moved;
    
    unsigned int _camType;
}
@property (nonatomic,retain) UITouch* panTouch;
@property (nonatomic,retain) UITouch* panTouch2;

- (void) startDisplayLink;
- (void) stopDisplayLink;
- (void) displayTick;

- (void) selectTradePost:(UITouch*)touch; 
- (void) showTradeMenu;
@end

@implementation GLViewController
@synthesize panTouch = _panTouch;
@synthesize panTouch2 = _panTouch2;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
    {
        _glView = nil;
        _displayLink = nil;
        _displayTickActive = NO;
        _previousTime = 0.0;

        _panTouch = nil;
        _panTouch2 = nil;
        _isRotating = YES;
        _isTwoFingerTranslation = NO;
        _moved = NO;
        
        _camType = CAMTYPE_PERSPECTIVE;
    }
    return self;
}

- (void) dealloc
{
    self.panTouch = nil;
    self.panTouch2 = nil;
    [self stopDisplayLink];
    GameManager::GetInstance()->FinishLocalGame();
    GameRenderer::DestroyInstance();
    [_glView release];
    [_buttonTransformToggle release];
    [_buttonCamToggle release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self.view setMultipleTouchEnabled:YES];
    _glView = (RendererGLView*) [self view];
    [EAGLContext setCurrentContext:_glView.context];
    GameRenderer::CreateInstance();
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    GameRenderer::GetInstance()->SetScreenWidth(screenBounds.size.width);
    GameRenderer::GetInstance()->SetScreenHeight(screenBounds.size.height);
    
    float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    GameRenderer::GetInstance()->SetMainCameraPerspective(kCameraFov, aspect, kCameraNearZ, kCameraFarZ);
    
    // start the game
    GameManager::GetInstance()->StartLocalGame();
    [self startDisplayLink];
}

- (void)viewDidUnload
{
    self.panTouch = nil;
    self.panTouch2 = nil;
    
    [self stopDisplayLink];
    GameManager::GetInstance()->FinishLocalGame();
    [EAGLContext setCurrentContext:_glView.context];
    GameRenderer::DestroyInstance();
    [_glView release];
    _glView = nil;
    [_buttonTransformToggle release];
    _buttonTransformToggle = nil;
    [_buttonCamToggle release];
    _buttonCamToggle = nil;
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - display link
- (void) startDisplayLink
{
    if(!_displayTickActive)
    {
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(displayTick)];
        [_displayLink setFrameInterval:kFrameInterval];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        _displayTickActive = YES;
    }
}

- (void) stopDisplayLink
{
    if(_displayTickActive)
    {
        [_displayLink invalidate];
        _displayLink = nil;
        _displayTickActive = NO;
    }
}

- (void) displayTick
{
    CFTimeInterval elapsed = 0.0;
    
    // update time
    if(_previousTime > 0.0)
    {
        elapsed = [_displayLink timestamp] - _previousTime;
    }
    else
    {
        elapsed = [_displayLink timestamp];
    }
    _previousTime = [_displayLink timestamp];
    if(elapsed > kMaxFrametime)
    {
        elapsed = kMaxFrametime;
    }
    
    GameManager::GetInstance()->Update(elapsed);
    GameRenderer::GetInstance()->AddDraw();
    
    [_glView beginFrame];
    GameRenderer::GetInstance()->Render();
    [_glView endFrame];
}

- (void) selectTradePost:(UITouch *)touch
{
    CGPoint touchPoint = [touch locationInView:self.view];
    float projX = 2.0f * ((touchPoint.x / self.view.bounds.size.width) - 0.5f);
    float projY = 2.0f * (0.5f - (touchPoint.y / self.view.bounds.size.height));
    TradePostLocal* selectedPost = GameManager::GetInstance()->SelectTradePost(projX, projY);
    if(selectedPost)
    {
        NSLog(@"selected %s", selectedPost->GetName());
        [self showTradeMenu];
    }
}

#pragma mark - touch events
static const float radiansIncr = M_PI_4 * 0.005f;
static const float moveIncr = 0.025f;
- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesBegan:touches withEvent:event];
    
    for(UITouch* cur in touches)
    {
        if(![self panTouch])
        {
            self.panTouch = [touches anyObject];
            _curPoint = [self.panTouch locationInView:self.view];
            _prevPoint = _curPoint;            
        }
        else if([self panTouch] != cur)
        {
            if(![self panTouch2])
            {
                // second touch
                self.panTouch2 = cur;
                _curPoint2 = [cur locationInView:self.view];
                _prevPoint2 = _curPoint2;
                _isTwoFingerTranslation = YES;
                break;
            }
        }
    }
    _moved = NO;
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesMoved:touches withEvent:event];
    BOOL moved = NO;
    CGPoint translation;
    if([self panTouch])
    {
        if([touches containsObject:[self panTouch]])
        {
            moved = YES;
            _prevPoint = _curPoint;
            _curPoint = [[self panTouch] locationInView:self.view];
            translation = CGPointMake(_curPoint.x - _prevPoint.x, _curPoint.y - _prevPoint.y);
        }
    }
    
    if([self panTouch2])
    {
        if([touches containsObject:[self panTouch2]])
        {
            moved = YES;
            _prevPoint2 = _curPoint2;
            _curPoint2 = [[self panTouch2] locationInView:self.view];
            if(!moved)
            {
                moved = YES;
                translation = CGPointMake(_curPoint2.x - _prevPoint2.x, _curPoint2.y - _prevPoint2.y);            
            }
        }
    }
    if(moved)
    {
        _moved = YES;
        if(_isRotating && !_isTwoFingerTranslation)
        {
            GameRenderer::GetInstance()->GetMainCamera()->IncrRotZ(translation.x * radiansIncr);
        }
        else 
        {
            GameRenderer::GetInstance()->GetMainCamera()->MovePlanar(-translation.x * moveIncr, translation.y * moveIncr);
        }
    }
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesEnded:touches withEvent:event];
    if((!_moved) && (!_isTwoFingerTranslation))
    {
        [self selectTradePost:[touches anyObject]];
    }
    self.panTouch = nil;
    self.panTouch2 = nil;
    _isTwoFingerTranslation = NO;
}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesCancelled:touches withEvent:event];
    self.panTouch = nil;
    self.panTouch2 = nil;
    _isTwoFingerTranslation = NO;
}


- (IBAction)toggleTransform:(id)sender 
{
    _isRotating = !_isRotating;
    if(_isRotating)
    {
        [_buttonTransformToggle setTitle:@"R" forState:UIControlStateNormal];
    }
    else 
    {
        [_buttonTransformToggle setTitle:@"T" forState:UIControlStateNormal];
    }
}

- (IBAction)toggleCamType:(id)sender 
{
    float aspect = fabsf(self.view.bounds.size.width / self.view.bounds.size.height);
    if(CAMTYPE_PERSPECTIVE == _camType)
    {
        _camType = CAMTYPE_ORTHO;
        [_buttonCamToggle setTitle:@"O" forState:UIControlStateNormal];
        GameRenderer::GetInstance()->SetMainCameraOrtho(kCameraOrthoAspectScale, aspect, kCameraNearZ, kCameraFarZ);
    }
    else 
    {
        _camType = CAMTYPE_PERSPECTIVE;
        [_buttonCamToggle setTitle:@"P" forState:UIControlStateNormal];
        GameRenderer::GetInstance()->SetMainCameraPerspective(kCameraFov, aspect, kCameraNearZ, kCameraFarZ);
    }
}

#pragma mark - Menus
- (void) showTradeMenu
{
    // do nothing
}

@end
