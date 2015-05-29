//
//  ViewController.h
//  SDK_DEMO
//  Created by sma11case 2/3/13.
//  Copyright (c) 20  2 13 张熙文. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PPAppPlatformKit/PPAppPlatformKit.h>

@interface PPLoginViewController : UIViewController<UITextFieldDelegate, PPAppPlatformKitDelegate>
{
    UIImageView *bgloginImageView;
    UIImageView *bgGanmeCenterImageView;
    UIButton *ppCenterButton;
    UIButton *pploginButton;
    UISegmentedControl *changeAddressButton;
    
    UIView *propView;
    NSArray *arrayName;
    NSArray *arrayPrice;
    UITextField *customAddresTextField;
    
    
    //购买商品的价格
    NSString *_price;
    //购买商品的名称
    NSString *_name;
    NSMutableData *recvData;
    int zoneId;
    NSString* roleId;
}

+ (PPLoginViewController*)sharedInstance;
- (void)showLoginView;
- (void)showGameCenterView;
- (void)showLoginImageView:(bool)show;
- (void)exchangeGoods:(double)price RoleId:(NSString *)paramRoldId ZoneId:(int)paramZoneId Title:(NSString *)title;
- (NSString*)currentUserName;
@end


