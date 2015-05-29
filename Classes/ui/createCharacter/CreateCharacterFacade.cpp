//
//  CreateCharacterFacade.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-2.
//
//

#include "CreateCharacterFacade.h"

bool CreateCharacterFacade::init()
{
    createCharacter = NULL;
    return true;
}

void CreateCharacterFacade::openCreateCharacterScene()
{
    CCScene *scene = CCScene::create();
    createCharacter = CreateCharacter::create();
    scene->addChild(createCharacter);
    if(CCDirector::sharedDirector()->getRunningScene())
    {
        CCDirector::sharedDirector()->replaceScene(scene);
    }else{
        CCDirector::sharedDirector()->runWithScene(scene);
    }
}
