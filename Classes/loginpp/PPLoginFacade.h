//
//  PPLoginFacade.h
//  legendofheros
//  Created by sma11case 13-11-15.
//
//

#ifndef __legendofheros__PPLoginFacade__
#define __legendofheros__PPLoginFacade__

#include <iostream>
#include <string>

using std::string;

class PPLoginFacade
{
public:
    string getUserName();
    void exchangeGoods(double price, string roleId, int zoneId, string title);
    void showLoginView();
    void showGameCenterView();
};
#endif /* defined(__legendofheros__PPLoginFacade__) */
