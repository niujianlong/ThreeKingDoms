//
//  IAPFacade.cpp
//  threeKingdoms
//  Created by sma11case 14-2-28.
//
//

#include "IAPFacade.h"
#import "IAPHelper.h"

void buy(int type)
{
    [[IAPHelper sharedInstance] buy:type];
}