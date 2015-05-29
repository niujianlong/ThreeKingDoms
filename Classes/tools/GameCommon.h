//
//  GameCommon.h
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#ifndef __threeKingdoms__GameCommon__
#define __threeKingdoms__GameCommon__

#include <iostream>

#ifndef INSTANCE
#define INSTANCE(_cName)        _cName::getInstance()
#define CLASS_INSTANCE(_cName) \
static _cName * getInstance() \
{ \
static _cName * pIns = NULL; \
if (pIns == NULL) { \
pIns = new _cName(); \
pIns->init(); \
} \
return pIns; \
}
#endif

#define ADD_TOUCH CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true)
#define REMOVE_TOUCH CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this)

#endif /* defined(__threeKingdoms__GameCommon__) */
