//
//  PPLoginFacade.cpp
//  legendofheros
//
//  Created by lee song on 13-11-15.
//
//

#include "PPLoginFacade.h"
#include "PPLoginViewController.h"

string PPLoginFacade::getUserName()
{
    return [[[PPLoginViewController sharedInstance] currentUserName] UTF8String];
}

void PPLoginFacade::exchangeGoods(double price, string roleId, int zoneId, string title)
{
    [[PPLoginViewController sharedInstance] exchangeGoods:price RoleId:[[NSString alloc] initWithUTF8String:roleId.c_str()] ZoneId:zoneId Title:[[NSString alloc] initWithUTF8String:title.c_str()]];
}

void PPLoginFacade::showLoginView()
{
    [[PPLoginViewController sharedInstance] showLoginView];
}

void PPLoginFacade::showGameCenterView()
{
    [[PPLoginViewController sharedInstance] showGameCenterView];
}