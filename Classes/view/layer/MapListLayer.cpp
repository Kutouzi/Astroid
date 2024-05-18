//
// Created by qq454 on 2022/03/24.
//


#include "MapListLayer.h"
#include "view/SceneManager.h"
#include "AudioEngine.h"

USING_NS_CC;

bool MapListLayer::init(){
    if (!Layer::init()){
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto backButton = MenuItemImage::create(
            "scene/maplistlayer/backbutton.png",
            "scene/maplistlayer/backedbutton.png",
            CC_CALLBACK_1(MapListLayer::MenuReturnCallback, this));
    backButton->setPosition(Vec2(origin.x + visibleSize.width - backButton->getContentSize().width/2,
                                 origin.y + backButton->getContentSize().height/2));
    backButton->setScale(0.8f);

    auto startButton = MenuItemImage::create(
            "scene/maplistlayer/startbutton.png",
            "scene/maplistlayer/startedbutton.png",
            CC_CALLBACK_1(MapListLayer::StartCallback, this));
    startButton->setPosition(Vec2(origin.x + visibleSize.width - startButton->getContentSize().width/2,
                                 origin.y + startButton->getContentSize().height + 100));
    startButton->setScale(0.8f);

    auto funcMenu = Menu::create(backButton,startButton, NULL);
    funcMenu->setPosition(Vec2::ZERO);
    this->addChild(funcMenu,1);

    return true;
}

Layer *MapListLayer::createScene() {
    return MapListLayer::create();
}
void MapListLayer::MenuReturnCallback(cocos2d::Ref* pSender){
    sm->MapListToStartMenuScene();
}
void MapListLayer::StartCallback(cocos2d::Ref* sSender){
    sm->ToGameScene();
}