//
// Created by qq454 on 2022/03/24.
//

#ifndef ASTROID_SCENEMANAGER_H
#define ASTROID_SCENEMANAGER_H

#include "cocos2d.h"
#include "entity/FileData.h"
#include "MapListScene.h"
#include "StartMenuScene.h"
#include "GameScene.h"
#include "ScoreScene.h"

using namespace cocos2d;

class SceneManager{
public:
    StartMenuScene* startMenuScene{};
    MapListScene* mapListScene{};
    GameScene* gameScene{};
    ScoreScene* scoreScene{};
    bool bOptionLayer= true;
    bool bStopLayer=true;
    void CreatScene();
    void ToStartMenuScene();
    void ToOptionLayer(int backgroundAudioID);
    void ToMapListScene(int backgroundAudioID);
    void ToGameScene();
    void ToScoreScene();
    void ScoreSceneToMapListScene();
    void MapListToStartMenuScene();
    void ToStopLayer(int backgroundAudioID);
    void ReturnGame();
    void ReturnMapListScene();
    static float AutoScale(const cocos2d::Size& v,cocos2d::Sprite *&sprite){
        float fScaleTimes = 1.0;
        if(sprite->getContentSize().height > v.height){
            fScaleTimes = v.height / sprite->getContentSize().height;
        } else if (sprite->getContentSize().height < v.height){
            fScaleTimes =  v.height / sprite->getContentSize().height;
        }
        return fScaleTimes;
    }
    static std::string AutoPathToSTDPath(const std::string& sPath,const std::string& subPath){
        std::string s = sPath.substr(0,sPath.find_last_of('/')).append("/"+subPath);
        std::string ss = s.substr(s.find("songs/"));
#ifdef WIN32
        return ss;
#else
        return s;
#endif
    }
};

#endif //ASTROID_SCENEMANAGER_H
