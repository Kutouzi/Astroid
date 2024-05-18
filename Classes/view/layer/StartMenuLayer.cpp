//
// Created by qq454 on 2022/03/24.
//

#include "StartMenuLayer.h"
#include "AudioEngine.h"
#include "service/InitBeatmap.h"
#include "view/MapListScene.h"
#include "util/RWCache.h"
#include "spine/spine-cocos2dx.h"
#include "util/XMLConfigUtil.h"

using namespace spine;
USING_NS_CC;

bool StartMenuLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    line = Sprite::create("scene/startmenu/line.png");
    line->setScale(SceneManager::AutoScale(visibleSize,line)*0.7f);
    line->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto player = Sprite::create("scene/startmenu/player.png");
    player->setPosition(Vec2(-600.0f, 800.0f));
    player->setScale(1.8f);
    line->addChild(player,1);

    playerStartButton = MenuItemImage::create(
            "scene/startmenu/playerstartbutton.png",
            "scene/startmenu/playerstartedbutton.png",
            CC_CALLBACK_1(StartMenuLayer::PlayerStartCallback, this));
    playerStartButton->setPosition(Vec2(-600.0f, 1250.0f));
    playerStartButton->setScale(0.9f);
    playerStartButton->setEnabled(false);
    playerStartButton->setVisible(false);

    playerStopButton = MenuItemImage::create(
            "scene/startmenu/playerstopbutton.png",
            "scene/startmenu/playerstopedbutton.png",
            CC_CALLBACK_1(StartMenuLayer::PlayerStopCallback, this));
    playerStopButton->setPosition(Vec2(-600.0f, 1250.0f));
    playerStopButton->setScale(0.9f);

    auto playerMenu = Menu::create(playerStartButton,playerStopButton, NULL);
    playerMenu->setPosition(Vec2::ZERO);
    line->addChild(playerMenu,2);

    auto closeButton = MenuItemImage::create(
            "scene/startmenu/closebutton.png",
            "scene/startmenu/closedbutton.png",
            CC_CALLBACK_1(StartMenuLayer::MenuCloseCallback, this));
    closeButton->setPosition(Vec2(800.0f, 50.0f));

    auto startButton = MenuItemImage::create(
            "scene/startmenu/startbutton.png",
            "scene/startmenu/startedbutton.png",
            CC_CALLBACK_1(StartMenuLayer::ToNextScene, this));
    startButton->setPosition(Vec2(800.0f, 800.0f));

    auto optionButton = MenuItemImage::create(
            "scene/startmenu/optionbutton.png",
            "scene/startmenu/optionedbutton.png",
            CC_CALLBACK_1(StartMenuLayer::ToOption, this));
    optionButton->setPosition(Vec2(800.0f, 1450.0f));

    auto mainMenu = Menu::create(closeButton, startButton, optionButton, NULL);
    mainMenu->setPosition(Vec2::ZERO);

    this->addChild(line, 1);
    line->addChild(mainMenu, 2);

    auto fileData = new FileData();
    RWCache::getInstance()->ReadPathCache(fileData);
    string s = fileData->getSPath();
    auto *initBeatmap = new InitBeatmap();
    Beatmap *beatmap = initBeatmap->DoInitBeatmap(s);
    string title = beatmap->song->getSEnArtist() + " - " + beatmap->song->getSEnTitle();
    TTFConfig labelConfig;
    labelConfig.fontFilePath ="fonts/arial.ttf";
    labelConfig.fontSize = 30;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.bold= true;
    titleLabel = Label::createWithTTF( labelConfig, title);
    titleLabel->setDimensions(500.0f,200.0f);
    titleLabel->setPosition(Vec2(350.0f, 500.0f));
    player->addChild(titleLabel,2);

    string audioPath = SceneManager::AutoPathToSTDPath(fileData->getSPath(),fileData->getSAudioFilePath());
    AudioEngine::preload(audioPath);
    backgroundAudioID = AudioEngine::play2d(audioPath, true,XMLConfigUtil::getInstance()->ReadConfig("Voice")*0.01f);
    auto skeletonNode =SkeletonAnimation::createWithJsonFile("sprites/ririsu/ririsu.json","sprites/ririsu/ririsu.atlas",2.0f);
    skeletonNode->setPosition(Vec2(-600.0f, 300.0f));
    skeletonNode->setAnimation(0, "mark", true);
    line->addChild(skeletonNode,3);

    delete fileData;
    delete initBeatmap;
    return true;
}

Layer* StartMenuLayer::createScene()
{
    return StartMenuLayer::create();
}

void StartMenuLayer::PlayerStartCallback(cocos2d::Ref* pSender){
    //AudioEngine::resume(backgroundAudioID);
    AudioEngine::resumeAll();
    playerStartButton->setEnabled(false);
    playerStartButton->setVisible(false);
    playerStopButton->setEnabled(true);
    playerStopButton->setVisible(true);
    //AudioEngine::getProfile();
}
void StartMenuLayer::PlayerStopCallback(cocos2d::Ref* pSender){
    AudioEngine::pauseAll();
    //AudioEngine::pause(backgroundAudioID);
    playerStartButton->setEnabled(true);
    playerStartButton->setVisible(true);
    playerStopButton->setEnabled(false);
    playerStopButton->setVisible(false);
    //AudioEngine::getProfile();
}

void StartMenuLayer::MenuCloseCallback(cocos2d::Ref* pSender){
    Director::getInstance()->end();
}
void StartMenuLayer::ToOption(cocos2d::Ref* pSender){
    sm->ToOptionLayer(backgroundAudioID);
}
void StartMenuLayer::ToNextScene(cocos2d::Ref* pSender){
    sm->ToMapListScene(backgroundAudioID);
}

void StartMenuLayer::ChangeTitleLabel(std::string s) {
    titleLabel->setString(s);
}
