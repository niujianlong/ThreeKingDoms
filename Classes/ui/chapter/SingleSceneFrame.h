//
//  SingleSceneFrame.h
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#ifndef __threeKingdoms__SingleSceneFrame__
#define __threeKingdoms__SingleSceneFrame__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class SingleSceneFrame:public CCNode
{
public:
    static SingleSceneFrame* create(int sceneId);
    SingleSceneFrame(int sceneId);
    ~SingleSceneFrame();
    
    virtual bool init();
private:
    void initContent();
    int sceneId;
    void helpHandler();
};

#endif /* defined(__threeKingdoms__SingleSceneFrame__) */
