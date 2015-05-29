//
//  threeKingdomsAppController.mm
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"

#include "TalkingData.h"

//#ifdef VERSION_PP
//#include "PPLoginViewController.h"
//#endif

@implementation AppController

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    [__glView setMultipleTouchEnabled:YES];
    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
//#if (defined VERSION_PP) || (defined VERSION_PPJB)
//    PPLoginViewController* ppViewController = [PPLoginViewController sharedInstance];
//    // 因为有EAGLView存在，所以不能简单的将ViewController替换掉，
//    // 解决方案是将SDK的view作为Subview添加。
//    //    [viewController.view addSubview:ppViewController.view];
//    // 2013.9.18更新。
//    // 据说这是正统的用法，上面的是野路子，会导致各种奇葩问题=.=。
//    [[EAGLView sharedEGLView] addSubview:ppViewController.view];
//    [ppViewController.view setMultipleTouchEnabled:YES];
//    [window makeKeyAndVisible];
//    
//    /**
//     *必须写在程序window初始化之后。详情请commad + 鼠标左键 点击查看接口注释
//     *初始化应用的AppId和AppKey。从开发者中心游戏列表获取（https://pay.25pp.com）
//     *设置是否打印日志在控制台
//     *设置充值页面初始化金额
//     *是否需要客户端补发订单（详情请查阅接口注释）
//     *用户注销后是否自动push出登陆界面
//     *是否开放充值页面【操作在按钮被弹窗】
//     *若关闭充值响应的提示语
//     *初始化SDK界面代码
//     */
//    [[PPAppPlatformKit sharedInstance] setAppId:2865 AppKey:@"c90b01824c3311e402a58e6677db9f87"];
//    [[PPAppPlatformKit sharedInstance] setIsNSlogData:YES];
//    [[PPAppPlatformKit sharedInstance] setRechargeAmount:10];
//    [[PPAppPlatformKit sharedInstance] setIsLongComet:YES];
//    [[PPAppPlatformKit sharedInstance] setIsLogOutPushLoginView:YES];
//    [[PPAppPlatformKit sharedInstance] setIsOpenRecharge:YES];
//    [[PPAppPlatformKit sharedInstance] setCloseRechargeAlertMessage:@"关闭充值提示语"];
//    [PPUIKit sharedInstance];
//    
//    [PPUIKit setIsDeviceOrientationLandscapeLeft:YES];
//    [PPUIKit setIsDeviceOrientationLandscapeRight:YES];
//    [PPUIKit setIsDeviceOrientationPortrait:YES];
//    [PPUIKit setIsDeviceOrientationPortraitUpsideDown:YES];
//    
//#endif

    [[UIApplication sharedApplication] setStatusBarHidden: YES];

    cocos2d::CCApplication::sharedApplication()->run();
    
    [[UIApplication sharedApplication] setIdleTimerDisabled: YES];
    
    [TalkingData setSignalReportEnabled:YES];
    [TalkingData sessionStarted:@"9FD0DBE3466FFC8341DE75FD228AABE7" withChannelId:@""];
    
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}


@end

