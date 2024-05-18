//
// Created by qq454 on 2022/03/23.
//

#include "StartMenuScene.h"
#include "service/FormatFileData.h"
#include "service/RandomSongAndBG.h"
#include "SceneManager.h"
#include "util/RWCache.h"

USING_NS_CC;

Scene *StartMenuScene::createScene(){
    return StartMenuScene::create();
}

bool StartMenuScene::init(){
    if ( !Scene::init() ){
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto fileData = new FileData();
    auto *formatFileData = new FormatFileData();
    formatFileData->DoFormatFileData();
    auto *randomSongAndBG = new RandomSongAndBG();
    randomSongAndBG->DoRandomSongAndBG(fileData);
    background = Sprite::create(SceneManager::AutoPathToSTDPath(fileData->getSPath(),fileData->getSBackGroundPath()));
    background->setScale(SceneManager::AutoScale(visibleSize,background));
    background->setColor(Color3B(200,200,200));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    RWCache::getInstance()->WritePathCache(fileData);
    delete randomSongAndBG;
    delete formatFileData;
    delete fileData;
    return true;
}

void StartMenuScene::ChangeBackground(std::string sBackgroundPath) {
    background->setTexture(sBackgroundPath);
    background->setScale(SceneManager::AutoScale(Director::getInstance()->getVisibleSize(),background));
}

