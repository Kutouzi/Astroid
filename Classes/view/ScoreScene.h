//
// Created by qq454 on 2022/03/28.
//

#ifndef ASTROID_SCORESCENE_H
#define ASTROID_SCORESCENE_H

#include "cocos2d.h"

class ScoreScene : public cocos2d::Scene{
private:
    cocos2d::Sprite *background{};
public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    CREATE_FUNC(ScoreScene);
};


#endif //ASTROID_SCORESCENE_H
