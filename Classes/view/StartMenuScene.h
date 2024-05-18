
#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"

class StartMenuScene : public cocos2d::Scene{
private:
    cocos2d::Sprite *background{};
public:
    static cocos2d::Scene * createScene();
    virtual bool init();
    void ChangeBackground(std::string sBackgroundPath);


    CREATE_FUNC(StartMenuScene);
};

#endif // __STARTMENU_SCENE_H__
