//
// Created by qq454 on 2022/03/23.
//

#include "MapListScene.h"
#include "entity/Beatmap.h"
#include "util/RWCache.h"
#include "SceneManager.h"

Scene *MapListScene::createScene(){
    return MapListScene::create();
}

bool MapListScene::init(){
    if ( !Scene::init() ){
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto fileData = new FileData();
    RWCache::getInstance()->ReadPathCache(fileData);
    background = Sprite::create(SceneManager::AutoPathToSTDPath(fileData->getSPath(),fileData->getSBackGroundPath()));
    background->setScale(SceneManager::AutoScale(visibleSize,background));
    background->setColor(Color3B(200,200,200));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);
    delete fileData;
    return true;
}

void MapListScene::ChangeBackground(std::string sBackgroundPath) {
    background->setTexture(sBackgroundPath);
    backgroundPath=sBackgroundPath;
    background->setScale(SceneManager::AutoScale(Director::getInstance()->getVisibleSize(),background));
}

const string &MapListScene::getBackgroundPath() const {
    return backgroundPath;
}



