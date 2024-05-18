//
// Created by qq454 on 2022/03/28.
//

#ifndef ASTROID_SCORELAYER_H
#define ASTROID_SCORELAYER_H

#include "cocos2d.h"
#include "view/SceneManager.h"

class ScoreLayer :public cocos2d::Layer{
public:
    SceneManager *sm{};
    static cocos2d::Layer * createScene();
    virtual bool init();
    CREATE_FUNC(ScoreLayer);

    void MenuReturnCallback(Ref *pSender);
};


#endif //ASTROID_SCORELAYER_H
