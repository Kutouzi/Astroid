//
// Created by qq454 on 2022/03/24.
//

#ifndef ASTROID_STARTMENULAYER_H
#define ASTROID_STARTMENULAYER_H

#include "cocos2d.h"
#include "view/SceneManager.h"

class StartMenuLayer : public cocos2d::Layer{
private:
    cocos2d::Label *titleLabel{};
    Sequence *action{};
    cocos2d::Sprite * line{};
public:
    SceneManager *sm{};
    cocos2d::MenuItemImage *playerStartButton{};
    cocos2d::MenuItemImage *playerStopButton{};
    int backgroundAudioID = 0;
    static cocos2d::Layer* createScene();
    virtual bool init();
    void MenuCloseCallback(cocos2d::Ref* pSender);
    void PlayerStartCallback(cocos2d::Ref* pSender);
    void ToOption(cocos2d::Ref* pSender);
    void PlayerStopCallback(cocos2d::Ref* pSender);
    void ToNextScene(cocos2d::Ref* pSender);
    void ChangeTitleLabel(std::string s);
    CREATE_FUNC(StartMenuLayer);
};


#endif //ASTROID_STARTMENULAYER_H
