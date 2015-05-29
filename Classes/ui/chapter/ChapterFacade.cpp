//
//  ChapterFacade.cpp
//  threeKingdoms
//  Created by sma11case 14-1-4.
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