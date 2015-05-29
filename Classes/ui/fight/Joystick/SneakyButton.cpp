#include "SneakyButton.h"

using namespace cocos2d;

void SneakyButton::onEnterTransitionDidFinish()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 1);
}

void SneakyButton::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool SneakyButton::initWithRect(CCRect rect)
{
	bool pRet = false;
	//if(CCSprite::init()){
    
    bounds = CCRectMake(0, 0, rect.size.width, rect.size.height);
    center = CCPointMake(rect.size.width/2, rect.size.height/2);
    status = 1; //defaults to enabled
    active = false;
    value = 0;
    isHoldable = 0;
    isToggleable = 0;
    radius = 32.0f;
    rateLimit = 1.0f/120.0f;
    
    setPosition(rect.origin); //not sure about this
    pRet = true;
	//}
	return pRet;
}

void SneakyButton::limiter(float delta)
{
	value = 0;
	this->unschedule(schedule_selector(SneakyButton::limiter));
	active = false;
}

void SneakyButton::setRadius(float r)
{
	radius = r;
	radiusSq = r*r;
}

void SneakyButton::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (active) return;
    
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        location = this->convertToNodeSpace(location);
        if(isContain(pTouch)){
            float dSq = location.x*location.x + location.y*location.y;
            if(radiusSq > dSq){
                active = true;
                if (!isHoldable && !isToggleable){
                    value = 1;
                    this->schedule(schedule_selector(SneakyButton::limiter), rateLimit);
                }
                if (isHoldable) value = 1;
                if (isToggleable) value = !value;
            }
        }else{
            
        }
    }

}

void SneakyButton::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (!active) return;
	
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        location = this->convertToNodeSpace(location);
        //Do a fast rect check before doing a circle hit check:
        if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
            int r = radius + 200;
            if(location.x < -r || location.x > r || location.y < -r || location.y > r){
                
            }else{
                if (isHoldable) value = 0;
                if (isHoldable||isToggleable) active = false;
            }
            
        }else{
            float dSq = location.x*location.x + location.y*location.y;
            if(radiusSq > dSq){
                if (isHoldable) value = 1;
            }
            else {
                if (isHoldable) value = 0; active = false;
            }
        }
    }
	
}

void SneakyButton::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (!active) return;
    
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        location = this->convertToNodeSpace(location);
        
        if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
            
        }else{
            if (isHoldable) value = 0;
            if (isHoldable||isToggleable) active = false;
        }
    }
//    float maxRadius = radius + 300;
//    if(location.x < -maxRadius || location.x > maxRadius || location.y < -maxRadius || location.y > maxRadius){
//        int r = radius + 400;
//        if(location.x < -r || location.x > r || location.y < -r || location.y > r){
//            
//        }else{
//            active = false;
//        }
//    }else{
//        if (isHoldable) value = 0;
//        if (isHoldable||isToggleable) active = false;
//    }
}

void SneakyButton::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	this->ccTouchesEnded(pTouches, pEvent);
}

void SneakyButton::touchDelegateRelease()
{
	this->release();
}

void SneakyButton::touchDelegateRetain()
{
	this->retain();
}

bool SneakyButton::isContain(cocos2d::CCTouch *touch)
{
    CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    location = this->convertToNodeSpace(location);
    if(location.x < -radius || location.x > radius || location.y < -radius || location.y > radius){
        return false;
    }
    return true;
}
