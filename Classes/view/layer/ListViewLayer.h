//
// Created by qq454 on 2022/03/24.
//

#ifndef ASTROID_LISTVIEWLAYER_H
#define ASTROID_LISTVIEWLAYER_H

#include "cocos2d.h"
#include "view/SceneManager.h"
#include "ui/UIListView.h"
#include "entity/Beatmap.h"

class ListViewLayer :public cocos2d::Layer{
private:
    cocos2d::ui::ListView *pListView{};
public:
    int backgroundAudioID = 0;

    int getBackgroundAudioId() const;
    ssize_t forwardIndex;
    SceneManager *sm{};
    Sprite * massage;
    static cocos2d::Layer* createScene();
    virtual bool init();
    vector<Beatmap*> beatmapList;
    void ListViewCallback(cocos2d::Ref* pSender,cocos2d::ui::ListView::EventType type);
    CREATE_FUNC(ListViewLayer);
    void ObjiceAddToList();
};


#endif //ASTROID_LISTVIEWLAYER_H
