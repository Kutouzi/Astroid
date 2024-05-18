//
// Created by qq454 on 2022/03/28.
//

#include "ScoreLayer.h"
#include "util/RWCache.h"

USING_NS_CC;

cocos2d::Layer *ScoreLayer::createScene() {
    return ScoreLayer::create();
}

bool ScoreLayer::init() {
    if(!Layer::init()){
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

//    std::string temp;
    std::string rank;
    auto score = RWCache::getInstance()->ReadScoreCache();
    if(score >= 0.8){
//        temp="scene/scorelayer/S.png";
        rank="scene/scorelayer/ranks.png";
    }else if(score <0.8 && score >= 0.6){
//        temp="scene/scorelayer/A.png";
        rank="scene/scorelayer/ranka.png";
    }else if(score <0.6 && score >=0.4){
//        temp="scene/scorelayer/B.png";
        rank="scene/scorelayer/rankb.png";
    }else{
//        temp="scene/scorelayer/C.png";
        rank="scene/scorelayer/rankc.png";
    }
//    auto ranks = Sprite::create(temp);
//    ranks->setScale(0.6);
//    ranks->setPosition(visibleSize.width - ranks->getContentSize().width*0.6*0.5,
//                      visibleSize.height - (visibleSize.height - ranks->getContentSize().height*0.6*0.5));
//    this->addChild(ranks,2);

    auto rankt = Sprite::create(rank);
    rankt->setPosition(visibleSize.width/2,visibleSize.height/2);

    this->addChild(rankt,3);

    auto backButton = MenuItemImage::create(
            "scene/scorelayer/backbutton.png",
            "scene/scorelayer/backedbutton.png",
            CC_CALLBACK_1(ScoreLayer::MenuReturnCallback, this));
    backButton->setPosition(Vec2(visibleSize.width - (visibleSize.width - backButton->getContentSize().width*0.5),
                                 visibleSize.height - (visibleSize.height - backButton->getContentSize().height*0.5)));
    backButton->setScale(0.8f);

    auto menu = Menu::create(backButton,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,3);

    return true;
}
void ScoreLayer::MenuReturnCallback(Ref *pSender){
    sm->ScoreSceneToMapListScene();
}