//
// Created by qq454 on 2022/04/23.
//

#ifndef GAME_RC_STOPLAYER_H
#define GAME_RC_STOPLAYER_H

#include "cocos2d.h"
#include "view/SceneManager.h"
#include "ui/UISlider.h"

using namespace cocos2d::ui;

class StopLayer : public cocos2d::Layer{
public:
    SceneManager *sm;
    int backgroundAudioID = 0;
    static StopLayer* createScene();
    void BackToGameCallback(cocos2d::Ref* pSender);
    void BackToMapListLayerCallback(cocos2d::Ref* pSender);
    virtual bool init();
    CREATE_FUNC(StopLayer);
};


#endif //GAME_RC_STOPLAYER_H
