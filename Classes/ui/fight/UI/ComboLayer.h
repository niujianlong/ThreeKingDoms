//
//  ComboLayer.h
//  threeKingdoms
//  Created by sma11case 14-1-14.
//
//

#ifndef __threeKingdoms__ComboLayer__
#define __threeKingdoms__ComboLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class ComboLayer:public CCLayer
{
public:
    CREATE_FUNC(ComboLayer);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initContent();
};


class ComboManager:public CCObject
{
public:
    CLASS_INSTANCE(ComboManager);
    bool init();
    
    void removeLayer();
    void showCombo(int currentMultiple);
private:
    int currentCombo;
    ComboLayer *layer;
    CCLabelBMFont *comboLabel;
    
    void hideComboLabel();
};


#endif /* defined(__threeKingdoms__ComboLayer__) */
