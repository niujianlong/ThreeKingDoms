#include "SneakyJoystick.h"

using namespace cocos2d;

#define SJ_PI 3.14159265359f
#define SJ_PI_X_2 6.28318530718f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f

SneakyJoystick::~SneakyJoystick()
{
}

bool SneakyJoystick::initWithRect(CCRect rect)
{
	bool pRet = false;
	//if(CCSprite::init()){
    stickPosition = CCPointZero;
    degrees = 0.0f;
    velocity = CCPointZero;
    autoCenter = true;
    isDPad = false;
    hasDeadzone = false;
    numberOfDirections = 4;
    active = false;
    
    this->setJoystickRadius(rect.size.width/2);
    this->setThumbRadius(32.0f);
    this->setDeadRadius(0.0f);
    
    //Cocos node stuff
    setPosition(rect.origin);
    pRet = true;
	//}
	return pRet;
}

void SneakyJoystick::onEnterTransitionDidFinish()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 1);
}

void SneakyJoystick::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

float round(float r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

void SneakyJoystick::updateVelocity(CCPoint point)
{
	// Calculate distance and angle from the center.
	float dx = point.x;
	float dy = point.y;
	float dSq = dx * dx + dy * dy;
	
	if(dSq <= deadRadiusSq){
		velocity = CCPointZero;
		degrees = 0.0f;
		stickPosition = point;
		return;
	}
    
	float angle = atan2f(dy, dx); // in radians
	if(angle < 0){
		angle		+= SJ_PI_X_2;
	}
	float cosAngle;
	float sinAngle;
	
	if(isDPad){
		float anglePerSector = 360.0f / numberOfDirections * SJ_DEG2RAD;
		angle = round(angle/anglePerSector) * anglePerSector;
	}
	
	cosAngle = cosf(angle);
	sinAngle = sinf(angle);
	
	// NOTE: Velocity goes from -1.0 to 1.0.
	if (dSq > joystickRadiusSq || isDPad) {
		dx = cosAngle * joystickRadius;
		dy = sinAngle * joystickRadius;
	}
	
	velocity = CCPointMake(dx/joystickRadius, dy/joystickRadius);
	degrees = angle * SJ_RAD2DEG;
	
	// Update the thumb's position
	stickPosition = ccp(dx, dy);
}

void SneakyJoystick::setIsDPad(bool b)
{
	isDPad = b;
	if(isDPad){
		hasDeadzone = true;
		this->setDeadRadius(10.0f);
	}
}

void SneakyJoystick::setJoystickRadius(float r)
{
	joystickRadius = r;
	joystickRadiusSq = r*r;
}

void SneakyJoystick::setThumbRadius(float r)
{
	thumbRadius = r;
	thumbRadiusSq = r*r;
}

void SneakyJoystick::setDeadRadius(float r)
{
	deadRadius = r;
	deadRadiusSq = r*r;
}

void SneakyJoystick::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        location = this->convertToNodeSpace(location);
        float maxRadius = joystickRadius + 200;
        float maxSq = maxRadius * maxRadius;
        if(location.x < -maxRadius || location.x > maxRadius || location.y < -maxRadius || location.y > maxRadius){
            
        }else{
            float dSq = location.x*location.x + location.y*location.y;
            if(maxSq > dSq){
                active = true;
                this->updateVelocity(location);
            }
        }
    }
}

void SneakyJoystick::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(!active) return;
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        location = this->convertToNodeSpace(location);
        float maxRadius = joystickRadius + 200;
        if(location.x < -maxRadius || location.x > maxRadius || location.y < -maxRadius || location.y > maxRadius){
            
        }else{
            this->updateVelocity(location);
        }
    }
}

void SneakyJoystick::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(!active) return;
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        location = this->convertToNodeSpace(location);
        float maxRadius = joystickRadius + 300;
        if(location.x < -maxRadius || location.x > maxRadius || location.y < -maxRadius || location.y > maxRadius){
            
        }else{
            CCPoint location = CCPointZero;
            if(!autoCenter){
                CCPoint location = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
                location = this->convertToNodeSpace(location);
            }
            this->updateVelocity(location);
            active = false;
        }
    }
    
}

void SneakyJoystick::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	this->ccTouchesEnded(pTouches, pEvent);
}

void SneakyJoystick::touchDelegateRelease()
{
	this->release();
}

void SneakyJoystick::touchDelegateRetain()
{
	this->retain();
}



