//
// Created by qq454 on 2022/03/24.
//

#include "SceneManager.h"
#include "view/layer/StartMenuLayer.h"
#include "view/layer/MapListLayer.h"
#include "view/layer/OptionLayer.h"
#include "StartMenuScene.h"
#include "MapListScene.h"
#include "view/layer/ListViewLayer.h"
#include "view/layer/GameLayer.h"
#include "view/layer/ScoreLayer.h"
#include "view/layer/StopLayer.h"
#include "AudioEngine.h"
#include "util/RWCache.h"
#include "util/XMLConfigUtil.h"

void SceneManager::CreatScene(){
    startMenuScene = StartMenuScene::create();
    StartMenuLayer * startMenuLayer = StartMenuLayer::create();
    startMenuLayer->setName("startMenuLayer");
    startMenuScene->addChild(startMenuLayer,1);
    startMenuLayer->sm=this;
    Director::getInstance()->runWithScene(startMenuScene);
}

void SceneManager::ToStartMenuScene() {
    OptionLayer *optionLayer = dynamic_cast<OptionLayer*> (startMenuScene->getChildByName("optionLayer"));
    optionLayer->setVisible(false);
    StartMenuLayer *startMenuLayer = dynamic_cast<StartMenuLayer*> (startMenuScene->getChildByName("startMenuLayer"));
    startMenuLayer->setVisible(true);
}

void SceneManager::MapListToStartMenuScene(){
    StartMenuLayer *startMenuLayer = dynamic_cast<StartMenuLayer*> (startMenuScene->getChildByName("startMenuLayer"));
    startMenuLayer->setVisible(true);
    ListViewLayer *listViewLayer = dynamic_cast<ListViewLayer*> (mapListScene->getChildByName("listViewLayer"));
    startMenuLayer->backgroundAudioID=listViewLayer->backgroundAudioID;
    Director::getInstance()->pushScene(TransitionFade::create(1.5f,startMenuScene));
//    startMenuScene->ChangeBackground(mapListScene->getBackgroundPath());
}

void SceneManager::ToMapListScene(int backgroundAudioID) {
    mapListScene = MapListScene::create();
    MapListLayer *mapListLayer = MapListLayer::create();
    mapListLayer->setName("mapListLayer");
    ListViewLayer *listViewLayer = ListViewLayer::create();
    listViewLayer->setName("listViewLayer");
    mapListScene->addChild(mapListLayer,1);
    mapListScene->addChild(listViewLayer,1);
    listViewLayer->backgroundAudioID=backgroundAudioID;
    mapListLayer->sm=this;
    listViewLayer->sm=this;
    Director::getInstance()->pushScene(TransitionFade::create(1.5f,mapListScene));
}

void SceneManager::ToOptionLayer(int backgroundAudioID) {
    OptionLayer *optionLayer;
    if(bOptionLayer){
        optionLayer = OptionLayer::create();
        optionLayer->setName("optionLayer");
        startMenuScene->addChild(optionLayer,10);
        optionLayer->sm=this;
        bOptionLayer= false;
    } else{
        optionLayer = dynamic_cast<OptionLayer*> (startMenuScene->getChildByName("optionLayer"));
    }
    optionLayer->backgroundAudioID=backgroundAudioID;
    StartMenuLayer *startMenuLayer = dynamic_cast<StartMenuLayer*> (startMenuScene->getChildByName("startMenuLayer"));
    startMenuLayer->setVisible(false);
    optionLayer->setVisible(true);
}

void SceneManager::ToGameScene() {
    gameScene = GameScene::create();
    GameLayer *gameLayer = GameLayer::create();
    gameLayer->setName("gameLayer");
    gameScene->addChild(gameLayer,1);
    gameLayer->sm = this;
    Director::getInstance()->pushScene(TransitionFade::create(1.5f,gameScene));
}

void SceneManager::ToScoreScene() {
    scoreScene = ScoreScene::create();
    ScoreLayer *scoreLayer = ScoreLayer::create();
    scoreLayer->setName("scoreLayer");
    scoreScene->addChild(scoreLayer,1);
    scoreLayer->sm=this;
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5f,scoreScene));
}

void SceneManager::ScoreSceneToMapListScene() {
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5f,mapListScene));
    auto f = new FileData();
    RWCache::getInstance()->ReadPathCache(f);
    AudioEngine::uncacheAll();
    int i = AudioEngine::play2d(SceneManager::AutoPathToSTDPath(f->getSPath(),f->getSAudioFilePath()),true,XMLConfigUtil::getInstance()->ReadConfig("Voice")*0.01f);
    StartMenuLayer *startMenuLayer = dynamic_cast<StartMenuLayer*> (startMenuScene->getChildByName("startMenuLayer"));
    startMenuLayer->backgroundAudioID=i;
    delete f;
}

void SceneManager::ReturnGame() {
    StopLayer *stopLayer = dynamic_cast<StopLayer*> (gameScene->getChildByName("stopLayer"));
    stopLayer->setVisible(false);
    GameLayer *gameLayer = dynamic_cast<GameLayer*> (gameScene->getChildByName("gameLayer"));
    gameLayer->setVisible(true);
    AudioEngine::resume(gameLayer->getIAudioId());
    gameLayer->resume();
}

void SceneManager::ReturnMapListScene() {
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.5f,mapListScene));
    auto f = new FileData();
    RWCache::getInstance()->ReadPathCache(f);
    AudioEngine::uncacheAll();
    int i = AudioEngine::play2d(SceneManager::AutoPathToSTDPath(f->getSPath(),f->getSAudioFilePath()),true,XMLConfigUtil::getInstance()->ReadConfig("Voice")*0.01f);
    StartMenuLayer *startMenuLayer = dynamic_cast<StartMenuLayer*> (startMenuScene->getChildByName("startMenuLayer"));
    startMenuLayer->backgroundAudioID=i;
    delete f;
}

void SceneManager::ToStopLayer(int backgroundAudioID) {
    StopLayer *stopLayer{};
    try{
        stopLayer = dynamic_cast<StopLayer*> (gameScene->getChildByName("stopLayer"));
    }catch (error_code){}
    if(bStopLayer || stopLayer == nullptr){
        stopLayer = StopLayer::create();
        stopLayer->setName("stopLayer");
        gameScene->addChild(stopLayer,10);
        stopLayer->sm=this;
        stopLayer->backgroundAudioID=backgroundAudioID;
        bStopLayer= false;
    }
    GameLayer *gameLayer = dynamic_cast<GameLayer*> (gameScene->getChildByName("gameLayer"));
    gameLayer->setVisible(false);
    stopLayer->setVisible(true);
}

