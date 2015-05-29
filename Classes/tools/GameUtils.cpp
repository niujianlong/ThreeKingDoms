//
//  GameUtils.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//
//

#include "GameUtils.h"
#include "JniManager.h"

bool GameUtils::init()
{
    return true;
}

CCPoint GameUtils::getWindowsCenterPosition()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint p = ccp(size.width/2, size.height/2);
    return p;
}

CCPoint GameUtils::getNodeCenterPosition(cocos2d::CCNode *node)
{
    return ccp(node->getContentSize().width/2,node->getContentSize().height/2);
}
int GameUtils::getRandom(int size)
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    srand(now.tv_usec);
    int r = rand()%size;
    return r;
}

int GameUtils::getRandomFromVector(vector<vector<float> > param)
{
    int random = getRandom(10000);
    int tempMin = 0;
    int tempMax = 0;
    int result = -1;
    for(int i=0;i<param.size();i++){
        tempMin = tempMax;
        tempMax = tempMax + param[i][1] * 10000;
        if(random >= tempMin && random < tempMax){
            result = int(param[i][0]);
            break;
        }
    }
    return result;
}

int GameUtils::getRandomFromVector(vector<int> param)
{
    int r = getRandom(param.size());
    return param[r];
}


bool GameUtils::getRandomFromFloat(float param)
{
    int r = getRandom(11);
    int probability = param * 10.0f;
    if(r <= probability){
        return true;
    }
    return false;
}

bool GameUtils::vectorContainInt(vector<int> v, int _p)
{
    for(int i=0;i<v.size();i++){
        if(_p == v[i]){
            return true;
        }
    }
    return false;
}

const char* GameUtils::getUniqueIdentifier()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    string result = INSTANCE(JniManager)->jniGetMac();
    CCLog(result.c_str());
    return result.c_str();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return "123321";
#endif
}