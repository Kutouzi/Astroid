//
// Created by qq454 on 2022/03/24.
//

#ifndef ASTROID_MAPLISTLAYER_H
#define ASTROID_MAPLISTLAYER_H

#include "cocos2d.h"
#include "view/SceneManager.h"

class MapListLayer :public cocos2d::Layer{
public:
    SceneManager *sm{};
    static cocos2d::Layer* createScene();
    virtual bool init();
    void MenuReturnCallback(cocos2d::Ref* pSender);
    void StartCallback(cocos2d::Ref* sSender);
    CREATE_FUNC(MapListLayer);
};


#endif //ASTROID_MAPLISTLAYER_H
