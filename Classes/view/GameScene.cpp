//
// Created by qq454 on 2022/03/25.
//

#include "GameScene.h"
#include "util/RWCache.h"
#include "SceneManager.h"

USING_NS_CC;

Scene *GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
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
    return true;
}

void GameScene::ChangeBackground(const std::string& sBackgroundPath) {
    background->setTexture(sBackgroundPath);
    background->setScale(SceneManager::AutoScale(Director::getInstance()->getVisibleSize(),background));
}
void GameScene::SetBackgroundColor(Color3B color3B){
    background->setColor(color3B);
}