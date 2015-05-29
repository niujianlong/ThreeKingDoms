//
//  Chapter.h
//  threeKingdoms
//
//  Created by .m on 14-1-4.
//
//

#ifndef __threeKingdoms__Chapter__
#define __threeKingdoms__Chapter__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CommonMoneyBar.h"
#include "CommonTitleBar.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class Chapter:public CCLayer,
public CCScrollViewDelegate
{
public:
    CREATE_FUNC(Chapter);
    
    Chapter();
    ~Chapter();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
private:
    void initContent();
    void initScrollView();
    
    CCControlButton *startBtn;
//    CCLabelBMFont *moneyLabel;
//    CCProgressTimer *moneyBar;
    CommonMoneyBar *moneyBar;
    CommonTitleBar *titleBar;
    
    CCLayer *layer;
    CCScrollView *scrollView;
    int currentSelectedSceneIndex;
    int frameWidth;
    int frameSpace;
    void adjustScrollView();
    
    vector<int> sceneIdVector;
    CCArray *frameArray;
    
    void startGame();
    void onBack();
    
    void updateMoney();
    
    void openSet();
    
    void startGuide();
};

#endif /* defined(__threeKingdoms__Chapter__) */
