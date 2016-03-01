#import "GameViewController.h"
#include "Application.hpp"

@interface GameViewController () {
    Application application;
}
@property (strong, nonatomic) EAGLContext *context;
- (void)setup;
- (void)tearDown;
@end

@implementation GameViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setup];
}

- (void)dealloc
{    
    [self tearDown];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDown];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)setup
{
    [EAGLContext setCurrentContext:self.context];

    NSString *root = [[NSBundle mainBundle] resourcePath];
    application.setup({ .rootPath = root.UTF8String });
}

- (void)tearDown
{
    [EAGLContext setCurrentContext:self.context];
}

- (void)update
{
    application.update(0);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    application.draw();
}

@end
