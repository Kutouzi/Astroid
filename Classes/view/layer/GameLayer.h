//
// Created by qq454 on 2022/03/25.
//

#ifndef ASTROID_GAMELAYER_H
#define ASTROID_GAMELAYER_H


#include "cocos2d.h"
#include "view/SceneManager.h"
#include "spine/spine-cocos2dx.h"
#include "entity/Astroid.h"
#include "ui/CocosGUI.h"

struct ObjStruct{
    Sprite *s;
    ui::Button *b;
    AstroidObject *obj;
    int x;
    int y;
    bool isTooHeight= false;
    int zOrder = 1;
    AstroidObjectEnums type = AstroidObjectEnums::TwinkleStar;
};

class GameLayer :public cocos2d::Layer{
private:
    int temp_x=0;
    int temp_y=0;
    double offset=0;
    int next_offset=0;
    int distance=0;
    int stdy=0;
    int jpy=0;
    int det=0;
    int topheight = 0;
    bool isCreated= false;
    bool size=true;
    bool isTooHeight= false;
    int zOrder = 65535;
    Size visibleSize{};
    bool isOnce= true;
    bool flag = true;
    cocos2d::ui::Button *playerStartButton = cocos2d::ui::Button::create(
            "scene/startmenu/playerstartbutton.png","scene/startmenu/playerstartedbutton.png");
    vector<float> hitOffsetList{};
    Astroid *astroid{};
    AstroidObject *temp{};
    AstroidObject *forward{};
    AstroidObjectEnums temp_type = AstroidObjectEnums::TwinkleStar;
    float ticktime = 0;
    spine::SkeletonAnimation *skeletonNode{};
    std::string sAudioPath;
    int iAudioID = 0;
    vector<ObjStruct*> starList{};
public:
    int getIAudioId() const;
private:
    ObjStruct *objtemp{};
    int index=0;
    int tsindex=0;
    int ssindex=0;
    cocos2d::Label *audioTime{};
    EventListenerCustom *listener{};
    Menu *funcMenu{};
    float effectVoice=1;
    double globaloffset=0.0;
    double prerender=0.0;
    Sprite *cont{};
    bool isAuto= false;
    unsigned int totalObj=0;
    unsigned int compObj=0;
    Label *score{};
    cocos2d::ui::LoadingBar *nextBar{};
    Vec2 starToPosition{};
    Sprite *nextBarOver1{};
    Sprite *nextBarOver2{};
    Sprite *nextBarOver3{};
public:
    SceneManager *sm{};
    static cocos2d::Layer * createScene();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    void AudioCallback(int audio, const std::string &s);
    virtual void update(float delta);
    void PreloadCallback(bool s);

    void PlayButtonCallback(Ref *pSender, ui::Widget::TouchEventType type);
    void StopScene(Ref * pSender);

};


#endif //ASTROID_GAMELAYER_H
