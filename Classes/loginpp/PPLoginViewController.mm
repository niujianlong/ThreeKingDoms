 //
//  ViewController.m
//  SDK_DEMO
//  Created by sma11case 2/3/13.
//  Copyright (c) 2013 Net Fly. All rights reserved.
//

//http://58.218.147.147:8082

#define UI_SCREEN_WIDTH                     [[UIScreen mainScreen] bounds].size.width
#define UI_SCREEN_HEIGHT                    [[UIScreen mainScreen] bounds].size.height
#define IMAGERESOURCEPATH               [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"GameImages"]
#define BUTTONWIDTH                 150
#define BUTTONHEIGHT                40

#import "PPLoginViewController.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "UserData.h"
#include "NoticeBox.h"
#include "RechargeManager.h"

#define GAMESERVER_PORT_TEST                 @"8850/login.php "
#define GAMESERVER_IP_TEST                   "58.218.147.147"

@interface PPLoginViewController ()

@end

@implementation PPLoginViewController

+ (PPLoginViewController *)sharedInstance
{
    static PPLoginViewController* sharedInstance = nil;
    if (!sharedInstance)
    {
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            sharedInstance = [[PPLoginViewController alloc] init];
        });
    }
    return sharedInstance;
}

- (void)showLoginView
{
    [bgloginImageView setHidden:NO];
    [[PPAppPlatformKit sharedInstance] showLogin];
}

- (void)showGameCenterView
{
    [[PPAppPlatformKit sharedInstance] showCenter];
}

- (void)showLoginImageView:(bool)show
{
    [bgloginImageView setHidden:!show];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // 如果需要透明，就不要设置背景色和背景图片
    //[self.view setBackgroundColor:[UIColor whiteColor]];
    
//    bgloginImageView = [[UIImageView alloc] init];
//    [bgloginImageView setUserInteractionEnabled:YES];
//
//    [bgloginImageView setFrame:CGRectMake(0, 0, UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT)];
//    [[self view] addSubview:bgloginImageView];
//    [bgloginImageView setHidden:NO];
//    
//    pploginButton = [UIButton buttonWithType:UIButtonTypeCustom];
//    [pploginButton setFrame:CGRectMake(0, 0, 150, 40)];
//    [pploginButton addTarget:self action:@selector(loginPressDown) forControlEvents:UIControlEventTouchUpInside];
//    [pploginButton setImage:[UIImage imageWithContentsOfFile:[IMAGERESOURCEPATH stringByAppendingPathComponent:@"button.png"]]
//                   forState:UIControlStateNormal];
////    [bgloginImageView addSubview:pploginButton];
//
//    NSArray *array = [NSArray arrayWithObjects:@"正式",@"测试",@"自定义", nil];
//    changeAddressButton = [[UISegmentedControl alloc] initWithItems:array];
//    [changeAddressButton setSelectedSegmentIndex:0];
//    [changeAddressButton addTarget:self action:@selector(changeAddressButtonPressDown:)
//     forControlEvents:UIControlEventValueChanged];
//    
//    [changeAddressButton setFrame:CGRectMake(10, 10, 150, 30)];
////    [bgloginImageView addSubview:changeAddressButton];
//    
//    customAddresTextField = [[UITextField alloc] init];
//    [customAddresTextField setFrame:CGRectMake(10, 50, 250, 35)];
//    [customAddresTextField setText:@"http://"];
//    [customAddresTextField setDelegate:self];
//    [customAddresTextField addTarget:self action:@selector(textFieldDidChange)
//            forControlEvents:UIControlEventEditingChanged];
//    [customAddresTextField setBorderStyle:UITextBorderStyleLine];
//    [bgloginImageView addSubview:customAddresTextField];
//    [customAddresTextField setHidden:YES];
//    
//    UILabel *loginLabel = [[UILabel alloc] init];
//    [loginLabel setBackgroundColor:[UIColor clearColor]];
//    [loginLabel setText:@"登 录"];
//    [loginLabel setFrame:CGRectMake(0, 0, BUTTONWIDTH, BUTTONHEIGHT)];
//    [loginLabel setTextAlignment:NSTextAlignmentCenter];
//    [pploginButton addSubview:loginLabel];
//    [loginLabel release];
//    
//      
//    bgGanmeCenterImageView = [[UIImageView alloc] init];
//    [bgGanmeCenterImageView setUserInteractionEnabled:YES];
//    [bgGanmeCenterImageView setFrame:CGRectMake(0, 0, UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT)];
//    [[self view] addSubview:bgGanmeCenterImageView];
//    [bgGanmeCenterImageView setHidden:YES];
//    
//    ppCenterButton = [UIButton buttonWithType:UIButtonTypeCustom];
//    [ppCenterButton setFrame:CGRectMake(0, 0, 150, 40)];
//    [ppCenterButton addTarget:self action:@selector(ppCenterPressDown) forControlEvents:UIControlEventTouchUpInside];
//    [ppCenterButton setImage:[UIImage imageWithContentsOfFile:[IMAGERESOURCEPATH stringByAppendingPathComponent:@"button.png"]]
//                    forState:UIControlStateNormal];
//    [bgGanmeCenterImageView addSubview:ppCenterButton];
//    
//    UILabel *gameLabel = [[UILabel alloc] init];
//    [gameLabel setBackgroundColor:[UIColor clearColor]];
//    [gameLabel setText:@"PP中心"];
//    [gameLabel setTextAlignment:NSTextAlignmentCenter];
//    [gameLabel setFrame:CGRectMake(0, 0, BUTTONWIDTH, BUTTONHEIGHT)];
//    [ppCenterButton addSubview:gameLabel];
//    [gameLabel release];
//    
//    propView = [[UIView alloc] init];
//    [propView setFrame:CGRectMake(0, 0, UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH / 3 * 2)];
//    [bgGanmeCenterImageView addSubview:propView];
//    arrayName = [[NSArray alloc] initWithObjects:@"红色球（1PP币）",@"黑色球（2PP币）",@"紫色球（3PP币）"
//                 ,@"黄色球（4PP币）"
//                 , nil];
//    arrayPrice = [[NSArray alloc] initWithObjects:@"1",@"2",@"3",@"4", nil];
//    
//    for (int i = 0; i < [arrayName count]; i++) {
//        
//        UIButton *buyButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
//        [buyButton setTag:i];
//        [buyButton setTitle:@"购 买" forState:UIControlStateNormal];
//        [buyButton addTarget:self action:@selector(buy:) forControlEvents:UIControlEventTouchUpInside];
//        UILabel *lbl = [[UILabel alloc] init];
//        [lbl setTextColor:[UIColor whiteColor]];
//        [lbl setText:[arrayName objectAtIndex:i]];
//        [lbl setBackgroundColor:[UIColor clearColor]];
//        [lbl setNumberOfLines:2];
//        if (i % 2 == 0) {
//            [lbl setFrame:CGRectMake(propView.frame.size.height / 2 - 100,  10 + i / 2 * 80, 100, 50)];
//            [buyButton setFrame:CGRectMake(propView.frame.size.height / 2 - 100, 60 + i / 2 * 80, 100, 30)];
//        }else{
//            [lbl setFrame:CGRectMake(propView.frame.size.height / 2 + 100,  10 + i / 2 * 80, 100, 50)];
//            [buyButton setFrame:CGRectMake(propView.frame.size.height / 2 + 100, 60 + i / 2 * 80, 100, 30)];
//        }
//        [propView addSubview:buyButton];
//        [propView addSubview:lbl];
//        [lbl release];
//    }
//    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        
        [pploginButton setCenter:CGPointMake(UI_SCREEN_WIDTH / 2, UI_SCREEN_HEIGHT / 2 + 30)];
        
        [bgloginImageView setImage:[UIImage imageWithContentsOfFile:[IMAGERESOURCEPATH stringByAppendingPathComponent:@"transparentBg.png"]]];
        [ppCenterButton setCenter:CGPointMake(UI_SCREEN_WIDTH / 2, UI_SCREEN_HEIGHT - 50)];
        [bgGanmeCenterImageView setImage:[UIImage imageWithContentsOfFile:[IMAGERESOURCEPATH stringByAppendingPathComponent:@"bg.png"]]];
    }else{
        
        [pploginButton setFrame:CGRectMake(UI_SCREEN_HEIGHT / 2 - BUTTONWIDTH / 2, UI_SCREEN_WIDTH / 2 + 10, 150, 40)];
        
        [bgloginImageView setImage:[UIImage imageWithContentsOfFile:[IMAGERESOURCEPATH stringByAppendingPathComponent:@"transparentBg.png"]]];
        [ppCenterButton setFrame:CGRectMake(UI_SCREEN_HEIGHT / 2 - 150 / 2, UI_SCREEN_WIDTH / 2 + 10, 150, 40)];
        [bgGanmeCenterImageView setImage:[UIImage imageWithContentsOfFile:[IMAGERESOURCEPATH stringByAppendingPathComponent:@"bg.png"]]];
    }
    UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    UIInterfaceOrientation interfaceOrientation = (UIInterfaceOrientation)orientation;
    [self willRotateToInterfaceOrientation:interfaceOrientation duration:NSTimeIntervalSince1970];
    
    [[PPAppPlatformKit sharedInstance] setDelegate:self];
}
#pragma mark ---------------------------------------------------- 登 录 -------------------------------------------------------


-(void)loginPressDown{
    /// <summary>
    /// 登陆从右边展示
    /// </summary>
    /// <returns>无返回</returns>
//    NSString *msg = [NSString stringWithFormat:@"已切换到%@",[[PPAppPlatformKit sharedInstance] currentAddress]];
//    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示" message:msg delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
//    
//    [alert show];
//    [alert release];
    [[PPAppPlatformKit sharedInstance] showLogin];
}

-(void)ppCenterPressDown{
    
    [[PPAppPlatformKit sharedInstance] showCenter];
}


-(void)changeAddressButtonPressDown:(id) sender{
//    [customAddresTextField setHidden:YES];
//    UISegmentedControl * myseg = (UISegmentedControl *) sender;
//    if (myseg.selectedSegmentIndex == 0) {
//        [[PPAppPlatformKit sharedInstance] setCurrentAddress:@"https://pay.25pp.com"];
//    }else if(myseg.selectedSegmentIndex == 1){
//        [[PPAppPlatformKit sharedInstance] setCurrentAddress:@"https://testpay.25pp.com"];
//    }else if(myseg.selectedSegmentIndex == 2){
//        [customAddresTextField setHidden:NO];
//    }
}

- (void)exchangeGoods:(double)price RoleId:(NSString *)paramRoldId ZoneId:(int)paramZoneId Title:(NSString *)title
{
//    
//    roleId = paramRoldId;
//    zoneId = paramZoneId;
//    _price = [NSString stringWithFormat:@"%f", price];
//    _name = title;
//    
//    [[PPAppPlatformKit sharedInstance] currentUserName];
//    [[PPAppPlatformKit sharedInstance] currentUserId];
//    
//    NSString *priStr = [NSString stringWithFormat:@"%.2lf",price ];
//    _price = [[NSString alloc] initWithFormat:@"%@",priStr];
//    
//    //请求兑换道具
//    [[PPAppPlatformKit sharedInstance] exchangeGoods:price BillNo:billNO BillTitle:_name RoleId:paramRoldId ZoneId:paramZoneId];
//    
//    [billNO release];
    
    int time = [[NSDate date] timeIntervalSince1970];
    NSString *billNO = [NSString stringWithFormat:@"%d",time];
    [[PPAppPlatformKit sharedInstance] exchangeGoods:price BillNo:billNO BillTitle:title RoleId:paramRoldId ZoneId:paramZoneId];
}

- (NSString*)currentUserName
{
    return [[PPAppPlatformKit sharedInstance] currentUserName];
}

-(void)sendRequest:(NSMutableURLRequest *)paramRequest
{
    if (![NSURLConnection canHandleRequest:paramRequest])
    {
        return;
    }
    NSURLConnection *connection = [[NSURLConnection alloc] initWithRequest:paramRequest delegate:self];
    if(connection){
        recvData = [[NSMutableData alloc] init];
    }
    [connection start];
    [connection release];
}

//字符串登录成功回调【实现其中一个就可以】
- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey{
    //字符串token验证方式
    MSG_GAME_SERVER_STR mgs_s = {};
    mgs_s.len_str =  41;
    mgs_s.commmand_str = 0xAA000022;
    memcpy(mgs_s.token_key_str, [paramStrToKenKey UTF8String], 33);

    //跳入游戏界面
    [bgGanmeCenterImageView setHidden:NO];
    [bgloginImageView setHidden:YES];
    [[PPAppPlatformKit sharedInstance] getUserInfoSecurity];
    
    char tokenKey[33];
    memcpy(tokenKey, mgs_s.token_key_str, 33);
    
    INSTANCE(UserData)->isPPLogin = true;
}

//2进制登录成功回调【实现其中一个就可以】
//- (void)ppLoginHexCallBack:(char *)paramHexToKen{
//
//    MSG_GAME_SERVER mgs = {};
//    mgs.len =  24;
//    mgs.commmand = 0xAA000021;
//    memcpy(mgs.token_key, paramHexToKen, 16);
//
//    //跳入游戏界面
//    [bgGanmeCenterImageView setHidden:NO];
//    [bgloginImageView setHidden:YES];
//    [[PPAppPlatformKit sharedInstance] getUserInfoSecurity];
//    memcpy(INSTANCE(User)->tokenKey, mgs.token_key, 16);
//    
//    INSTANCE(User)->isPPLogin = true;
//    INSTANCE(User)->isLogin = true;
//}

//关闭客户端页面回调方法
-(void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode{
    //可根据关闭的VIEW页面做你需要的业务处理
    NSLog(@"当前关闭的VIEW页面回调是%d", paramPPPageCode);
}

//关闭WEB页面回调方法
- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode{
    //可根据关闭的WEB页面做你需要的业务处理
    NSLog(@"当前关闭的WEB页面回调是%d", paramPPWebViewCode);
}

//注销回调方法
- (void)ppLogOffCallBack{
    NSLog(@"注销的回调");
    [bgGanmeCenterImageView setHidden:YES];
    [bgloginImageView setHidden:NO];
    INSTANCE(UserData)->isPPLogin = false;
}

//兑换回调接口【只有兑换会执行此回调】
- (void)ppPayResultCallBack:(PPPayResultCode)paramPPPayResultCode{
    NSLog(@"兑换回调返回编码%d",paramPPPayResultCode);
    //回调购买成功。其余都是失败
    if(paramPPPayResultCode == PPPayResultCodeSucceed){
        //购买成功发放道具
        INSTANCE(RechargeManager)->rechargeVerification();
        
    }else{
        
    }
}

-(void)ppVerifyingUpdatePassCallBack{
    NSLog(@"验证游戏版本完毕回调");
    [[PPAppPlatformKit sharedInstance] showLogin];
}

#pragma mark      ---------------------ios supportedInterfaceOrientations -------------
//iOS 6.0旋屏
- (BOOL)shouldAutorotate
{
    return YES;
}


//iOS 6.0旋屏
- (NSUInteger)supportedInterfaceOrientations
{
    /**iOS6以上旋屏处理。默认SDK与游戏客户端支持方向是同步的，也就是说游戏支持什么方向旋转，SDK则也支持。游戏不支持该方向。SDK也不支持。
     *如果特殊方向不需要SDK旋转，而游戏需要支持。请将PPUserUIKit所不支持的方向设置NO。
     *至少要保持一个方向为YES
     */
//    [PPUIKit setIsDeviceOrientationLandscapeLeft:NO];
//    [PPUIKit setIsDeviceOrientationLandscapeRight:NO];
//    [PPUIKit setIsDeviceOrientationPortrait:NO];
//    [PPUIKit setIsDeviceOrientationPortraitUpsideDown:NO]
//    return UIInterfaceOrientationMaskLandscape;
    return UIInterfaceOrientationMaskAll;
}


//iOS 6.0以下旋屏
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    /**iOS6以下旋屏处理。默认SDK与游戏客户端支持方向是同步的，也就是说游戏支持什么方向旋转，SDK则也支持。游戏不支持该方向。SDK也不支持。
     *如果特殊方向不需要SDK旋转，而游戏需要支持。请将PPUserUIKit所不支持的方向设置NO。
     *至少要保持一个方向为YES
     */

//    [PPUIKit setIsDeviceOrientationLandscapeLeft:NO];
//    [PPUIKit setIsDeviceOrientationLandscapeRight:NO];
//    [PPUIKit setIsDeviceOrientationPortrait:NO];
//    [PPUIKit setIsDeviceOrientationPortraitUpsideDown:NO]
    if (UIInterfaceOrientationIsLandscape(interfaceOrientation)) {
        return YES;
    }
    return YES;
}


-(void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
                               duration:(NSTimeInterval)duration
{
	CGRect screenRect = [[UIScreen mainScreen] bounds];
	CGRect rect = CGRectZero;

    if(toInterfaceOrientation == UIInterfaceOrientationPortrait || toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
    {
        [propView setFrame:CGRectMake(0, 0, UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT / 3 * 2)];
        [ppCenterButton setCenter:CGPointMake(UI_SCREEN_WIDTH / 2, UI_SCREEN_HEIGHT - 50)];
        [pploginButton setCenter:CGPointMake(UI_SCREEN_WIDTH / 2 , UI_SCREEN_HEIGHT / 2)];
        [changeAddressButton setCenter:CGPointMake(UI_SCREEN_WIDTH / 2 , UI_SCREEN_HEIGHT / 2 + 50)];
        [customAddresTextField setCenter:CGPointMake(UI_SCREEN_WIDTH / 2 , UI_SCREEN_HEIGHT / 2 - 90)];
        
        
		rect = screenRect;
	}
	else if(toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft || toInterfaceOrientation == UIInterfaceOrientationLandscapeRight)
	{
        [propView setFrame:CGRectMake(0, 0, UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH / 3 * 2)];
        [ppCenterButton setCenter:CGPointMake(UI_SCREEN_HEIGHT / 2, UI_SCREEN_WIDTH - 50)];
        [pploginButton setCenter:CGPointMake(UI_SCREEN_HEIGHT / 2, UI_SCREEN_WIDTH / 2 + 30)];
        [changeAddressButton setCenter:CGPointMake(UI_SCREEN_HEIGHT / 2, UI_SCREEN_WIDTH / 2 + 80)];
        [customAddresTextField setCenter:CGPointMake(UI_SCREEN_HEIGHT / 2, UI_SCREEN_WIDTH / 2 - 120)];
        rect.size = CGSizeMake( screenRect.size.height, screenRect.size.width );
    }
    bgloginImageView.frame = rect;
    bgGanmeCenterImageView.frame = rect;
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma NSURLConnection delegate Methods
-(void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    [recvData setLength:0];
}

-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [recvData appendData:data];
}


-(void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    [recvData release];
}


-(void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    NSString *jsonString = [[NSString alloc] initWithData:recvData encoding:NSUTF8StringEncoding];
    NSLog(@"请求返回的dic -%@",jsonString);
    [recvData release];
    
}

-(void) dealloc{
    [super dealloc];
}

@end
