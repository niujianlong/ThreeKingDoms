//
//  NoticeManager.h
//  threeKingdoms
//
//  Created by .m on 14-1-16.
//
//

#ifndef __threeKingdoms__NoticeManager__
#define __threeKingdoms__NoticeManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class NoticeManager:public CCObject
{
public:
    CLASS_INSTANCE(NoticeManager);
    bool init();
    
    void showNotice(CCPoint targetPosition,CCNode *targetNode,float duration);
    
    void showNotice(CCPoint targetPosition,float duration,string bgImgPath,string fontPath,string content,CCPoint offset = ccp(0,0));
private:
    CCSize winSize;
};

#endif /* defined(__threeKingdoms__NoticeManager__) */
