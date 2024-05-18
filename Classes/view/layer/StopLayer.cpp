//
// Created by qq454 on 2022/04/23.
//

#include "StopLayer.h"
#include "AudioEngine.h"

using namespace cocos2d::ui;
USING_NS_CC;

StopLayer *StopLayer::createScene() {
    return StopLayer::create();
}

void StopLayer::BackToGameCallback(cocos2d::Ref *pSender) {
    sm->ReturnGame();
}

void StopLayer::BackToMapListLayerCallback(cocos2d::Ref *pSender) {
    sm->ReturnMapListScene();
}

bool StopLayer::init() {
    if ( !Layer::init() ){
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("scene/stoplayer/stoplayer.png");
    background->setScale(SceneManager::AutoScale(visibleSize,background) * 0.8f);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);

    auto backButton = MenuItemImage::create(
            "scene/stoplayer/continue.png",
            "scene/stoplayer/continue.png",
            CC_CALLBACK_1(StopLayer::BackToGameCallback, this));
    backButton->setPosition(Vec2(600.0f, 400.0f));

    auto backButton2 = MenuItemImage::create(
            "scene/stoplayer/returntomaplist.png",
            "scene/stoplayer/returntomaplist.png",
            CC_CALLBACK_1(StopLayer::BackToMapListLayerCallback, this));
    backButton2->setPosition(Vec2(600.0f, 200.0f));

    auto funcMenu = Menu::create(backButton, backButton2,NULL);
    funcMenu->setPosition(Vec2::ZERO);
    background->addChild(funcMenu,11);

    return true;
}
