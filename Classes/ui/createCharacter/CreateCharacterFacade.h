//
//  CreateCharacterFacade.h
//  threeKingdoms
//
//  Created by .m on 14-1-2.
//
//

#ifndef __threeKingdoms__CreateCharacterFacade__
#define __threeKingdoms__CreateCharacterFacade__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "CreateCharacter.h"

using namespace std;
USING_NS_CC;

class CreateCharacterFacade:public CCObject
{
public:
    CLASS_INSTANCE(CreateCharacterFacade);
    bool init();
    
    void openCreateCharacterScene();
    
private:
    CreateCharacter *createCharacter;
};

#endif /* defined(__threeKingdoms__CreateCharacterFacade__) */
