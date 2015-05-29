//
//  ComboLayer.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-14.
//
//

#include "ComboLayer.h"
#include "GameUtils.h"
#include "SceneManager.h"
#include "FightManager.h"

bool ComboLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    initContent();
    return true;
}


void ComboLayer::initContent()
{
    
}

void ComboLayer::onEnter()
{
    CCLayer::onEnter();
    setPosition(getCenterPosition(this));
}

void ComboLayer::onExit()
{
    CCLayer::onExit();
    INSTANCE(ComboManager)->removeLayer();
}

bool ComboManager::init()
{
    layer = NULL;
    comboLabel = NULL;
    currentCombo = 0;
    return true;
}

void ComboManager::showCombo(int currentMultiple)
{
    if(layer == NULL){
        layer = ComboLayer::create();
        INSTANCE(SceneManager)->addToCurrentScene(layer, zOrder_notice);
        comboLabel = CCLabelBMFont::create("combo", "font/font_combo.fnt");
        //        comboLabel->setVisible(false);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        comboLabel->setPosition(ccp(winSize.width/2 - 240, 140));
        layer->addChild(comboLabel);
    }
    currentCombo++;
//    if(currentCombo == 1){
//        comboLabel->setVisible(false);
//    }else{
//        comboLabel->setVisible(true);
//    }
    
    comboLabel->setOpacity(255);
    comboLabel->setString(CCString::createWithFormat("%d combo(%d)",currentCombo,currentMultiple)->getCString());
    comboLabel->stopAllActions();
    CCSequence *sequence = CCSequence::create(CCDelayTime::create(0.5),CCFadeOut::create(0.3),CCCallFunc::create(this,callfunc_selector(ComboManager::hideComboLabel)),NULL);
    
    comboLabel->runAction(sequence);
}

void ComboManager::hideComboLabel()
{
    currentCombo = 0;
}

void ComboManager::removeLayer()
{
    currentCombo = 0;
    layer = NULL;
    if(comboLabel){
        comboLabel->removeFromParent();
        comboLabel = NULL;
    }
    
}