//
//  ChapterFacade.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-4.
//
//

#include "ChapterFacade.h"

bool ChapterFacade::init()
{
    chapter = NULL;
    lastSelectedIndex = 0;
    return true;
}

void ChapterFacade::openChapterScene()
{
    CCScene *scene = CCScene::create();
    chapter = Chapter::create();
    scene->addChild(chapter);
    CCDirector::sharedDirector()->replaceScene(scene);
}

void ChapterFacade::setLastSelectedIndex(int index)
{
    lastSelectedIndex = index;
}

int ChapterFacade::getLastSelectedIndex()
{
    return lastSelectedIndex;
}