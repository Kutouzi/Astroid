//
// Created by qq454 on 2022/03/22.
//

#ifndef __MAPLIST_SCENE_H__
#define __MAPLIST_SCENE_H__

#include "cocos2d.h"

class MapListScene : public cocos2d::Scene{
private:
    cocos2d::Sprite *background{};
    std::string backgroundPath;
public:
    const std::string &getBackgroundPath() const;
    static cocos2d::Scene * createScene();
    virtual bool init();
    void ChangeBackground(std::string sBackgroundPath);
    CREATE_FUNC(MapListScene);

};


#endif //ASTROID_MAPLISTSCENE_H
