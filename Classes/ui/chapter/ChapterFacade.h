//
//  ChapterFacade.h
//  threeKingdoms
//  Created by sma11case 14-1-4.
//
//

#ifndef __threeKingdoms__ChapterFacade__
#define __threeKingdoms__ChapterFacade__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "Chapter.h"

using namespace std;
USING_NS_CC;

class ChapterFacade:public CCObject
{
public:
    CLASS_INSTANCE(ChapterFacade);
    bool init();
    
    void openChapterScene();
    
    int getLastSelectedIndex();
    void setLastSelectedIndex(int index);
private:
    Chapter *chapter;
    
    int lastSelectedIndex;
};

#endif /* defined(__threeKingdoms__ChapterFacade__) */
