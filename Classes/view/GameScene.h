//
// Created by qq454 on 2022/03/25.
//

#ifndef ASTROID_GAMESCENE_H
#define ASTROID_GAMESCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Scene{
private:
    cocos2d::Sprite *background{};
public:
    void ChangeBackground(const std::string& sBackgroundPath);
    static cocos2d::Scene * createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    void SetBackgroundColor(cocos2d::Color3B color3B);
};


#endif //ASTROID_GAMESCENE_H
