//
// Created by qq454 on 2022/03/25.
//

#include "GameLayer.h"
#include "util/RWCache.h"
#include "spine/spine-cocos2dx.h"
#include "service/OsuToAst.h"
#include "AudioEngine.h"
#include "util/XMLConfigUtil.h"

using namespace ui;
using namespace spine;
USING_NS_CC;

Layer *GameLayer::createScene() {
    return GameLayer::create();
}

bool GameLayer::init() {
    if ( !Layer::init() ){
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    this->setPosition(origin);

    auto fileData = new FileData();

    RWCache::getInstance()->ReadPathCache(fileData);
    std::string s = fileData->getSPath();

    auto di = Sprite::create("scene/gamelayer/di.png");
    di->setPosition(Vec2(visibleSize.width/2,  0));
    this->addChild(di,1);

    skeletonNode =SkeletonAnimation::createWithJsonFile("sprites/ririsu/ririsu.json","sprites/ririsu/ririsu.atlas",0.6f);
    skeletonNode->setPosition(Vec2(0.0f, visibleSize.height/19));
    skeletonNode->setAnimation(0, "mark", true);
    //skeletonNode->setAnchorPoint(Vec2(skeletonNode->getContentSize().width/2,skeletonNode->getContentSize().height));
    this->addChild(skeletonNode,3);

    stdy=skeletonNode->getAnchorPoint().y + 100;
    jpy=visibleSize.height/19;
    topheight= visibleSize.height * 18 /19;

    playerStartButton->addTouchEventListener(CC_CALLBACK_2(GameLayer::PlayButtonCallback,this));
    playerStartButton->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    playerStartButton->setScale(0.9f);
    playerStartButton->setEnabled(true);
    playerStartButton->setVisible(true);
    this->addChild(playerStartButton,7);

    nextBar=LoadingBar::create("scene/gamelayer/bar.png");
    nextBar->setPercent(100);
    nextBar->setScale(0.8);
    nextBar->setPosition(Vec2(nextBar->getContentSize().width*0.8/2.0f,visibleSize.height-nextBar->getContentSize().height*0.8/2.0f));
    this->addChild(nextBar,5);

    nextBarOver1 = Sprite::create("scene/gamelayer/barover1.png");
    nextBarOver1->setScale(0.8);
    nextBarOver1->setPosition(Vec2(nextBarOver1->getContentSize().width*0.8/2.0f,visibleSize.height-nextBar->getContentSize().height*0.8/2.0f));
    this->addChild(nextBarOver1,6);

    nextBarOver2 = Sprite::create("scene/gamelayer/barover2.png");
    nextBarOver2->setScale(0.8);
    nextBarOver2->setPosition(Vec2(nextBarOver2->getContentSize().width*0.8/2.0f+65,visibleSize.height-nextBar->getContentSize().height*0.8/2.0f-15));
    this->addChild(nextBarOver2,6);

    nextBarOver3 = Sprite::create("scene/gamelayer/barover3.png");
    nextBarOver3->setScale(0.8);
    nextBarOver3->setPosition(Vec2(nextBarOver3->getContentSize().width*0.8/2.0f+125,visibleSize.height-nextBar->getContentSize().height*0.8/2.0f+10));
    this->addChild(nextBarOver3,6);

    auto beatmap = new Beatmap();
    auto osuToAst = new OsuToAst();
    astroid = new Astroid();
    osuToAst->DoOsuToAst(s,beatmap,astroid);



    auto stopButton = MenuItemImage::create(
            "scene/gamelayer/playerstopbutton.png",
            "scene/gamelayer/playerstopedbutton.png",
            CC_CALLBACK_1(GameLayer::StopScene, this));
    stopButton->setPosition(Vec2(visibleSize.width - stopButton->getContentSize().width/2, visibleSize.height - stopButton->getContentSize().height/2));
    //stopButton->setScale(0.5f);

    funcMenu = Menu::create(stopButton,NULL);
    funcMenu->setPosition(Vec2::ZERO);
    funcMenu->setVisible(false);
    this->addChild(funcMenu,1);

    sAudioPath = SceneManager::AutoPathToSTDPath(s,fileData->getSAudioFilePath());
    AudioEngine::uncacheAll();
    AudioEngine::preload("scene/gamelayer/hit.mp3");

    TTFConfig labelConfig;
    labelConfig.fontFilePath ="fonts/arial.ttf";
    labelConfig.fontSize = 40;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.bold= true;

    size=astroid->astroidObject.size()-1;
    totalObj=astroid->astroidObject.size();

    bool isF= true;
    for(auto it:astroid->astroidObject){
        it->getDistance();
        forward = it;
        if(it->getEObjectType() == AstroidObjectEnums::TwinkleStar){
            auto o = new ObjStruct();
            o->type=AstroidObjectEnums::TwinkleStar;

            if(isF){
                o->x = it->getX();
                o->y = stdy;
                isF= false;
            } else{
                temp = it;
                if(forward->getX() > temp->getX()){
                    temp_x = temp->getX() - it->getDistance();
                    //temp_type = AstroidObjectEnums::TwinkleStar;
                } else{
                    temp_x = temp->getX() + it->getDistance();
                    //temp_type = AstroidObjectEnums::TwinkleStar;
                }
                temp_y = stdy;

                o->x=temp_x;
                o->y=temp_y;
            }

            auto ts = Sprite::create("scene/gamelayer/ts.png");
            ts->setScale(0);
            ts->setPosition(o->x,o->y);
            ts->setVisible(false);
            this->addChild(ts,zOrder);

            auto tsb =Button::create("scene/gamelayer/tsb.png");
            tsb->setScale(0);
            tsb->setPosition(Vec2(o->x,jpy));
            tsb->setTouchEnabled(true);
            tsb->addTouchEventListener([=](Ref * pSender,Widget::TouchEventType type){
                if(type == Widget::TouchEventType::BEGAN){
                    AudioEngine::play2d("scene/gamelayer/hit.mp3", false,effectVoice);
                    ts->setVisible(false);
                    auto button = dynamic_cast<Button*> (pSender);
                    button->setVisible(false);
                    hitOffsetList.emplace_back(det);
                    compObj = hitOffsetList.size();
                    score->setString(to_string(compObj)+" / "+to_string(totalObj));
                    auto s = Sprite::create("scene/gamelayer/fs.png");
                    s->setPosition(o->x,o->y);
                    this->addChild(s,zOrder-1);
                    s->runAction(Sequence::create(FadeIn::create(0.2f),
                                                  MoveTo::create(1.0f,starToPosition),
                                                  FadeOut::create(0.01f),
                                                  cont->runAction(Sequence::create(ScaleTo::create(0.1f,1.1),
                                                                                   ScaleTo::create(0.3f,1.0), nullptr)),
                                                  nullptr));
                }
            });
            tsb->setVisible(false);
            this->addChild(tsb,zOrder);
            o->s=ts;
            o->b=tsb;
            o->obj=it;
            starList.emplace_back(o);
        } else{
            auto o = new ObjStruct();
            o->type=AstroidObjectEnums::StreamStar;

            if(isF){
                isF= false;
                temp_x=it->getX();
                temp_y=it->getY();
                if(it->getHeight() >topheight){
                    o->isTooHeight = true;
                }else{
                    o->isTooHeight = false;
                }
            } else{
                temp=it;
                if(forward->getX() > temp->getX()){
                    temp_x = temp->getX() - it->getDistance();
                    temp_y = temp->getHeight();
                    temp_type = AstroidObjectEnums::StreamStar;
                    if(temp_y >topheight){
                        o->isTooHeight = true;
                    }else{
                        o->isTooHeight = false;
                    }
                } else{
                    temp_x = temp->getX() + it->getDistance();
                    temp_y = temp->getHeight();
                    temp_type = AstroidObjectEnums::StreamStar;
                    if(temp_y >topheight){
                        o->isTooHeight = true;
                    }else{
                        o->isTooHeight = false;
                    }
                }
                o->x=temp_x;
                o->y=temp_y;
            }

            auto ss = Sprite::create("scene/gamelayer/ss.png");
            ss->setScale(0);
            if(o->isTooHeight){
                ss->setPosition(o->x,topheight);
            } else{
                ss->setPosition(o->x,o->y);
            }
            ss->setVisible(false);
            this->addChild(ss,zOrder);

            auto ssb = Button::create("scene/gamelayer/ssb.png");
            ssb->setScale(0);
            ssb->setPosition(Vec2(o->x,jpy));
            ssb->setTouchEnabled(true);
            ssb->addTouchEventListener([=](Ref * pSender,Widget::TouchEventType type){
                auto button = dynamic_cast<Button*> (pSender);
                if(type == Widget::TouchEventType::BEGAN){
                    AudioEngine::play2d("scene/gamelayer/hit.mp3", false,effectVoice);
                }
                if(type == Widget::TouchEventType::ENDED){
                    ss->setVisible(false);
                    button->setVisible(false);
                    hitOffsetList.emplace_back(det);
                    compObj = hitOffsetList.size();
                    score->setString(to_string(compObj)+" / "+to_string(totalObj));
                    if(isTooHeight){
                        auto s = Sprite::create("scene/gamelayer/fs.png");
                        s->setPosition(o->x,topheight);
                        this->addChild(s,zOrder-1);
                        s->runAction(Sequence::create(FadeIn::create(0.2f),
                                                      MoveTo::create(1.0f,starToPosition),
                                                      FadeOut::create(0.01f),
                                                      cont->runAction(Sequence::create(ScaleTo::create(0.1f,1.1),
                                                                                       ScaleTo::create(0.3f,1.0), nullptr)),
                                                      nullptr));
                    } else{
                        auto s = Sprite::create("scene/gamelayer/fs.png");
                        s->setPosition(o->x,o->y);
                        this->addChild(s,zOrder-1);
                        s->runAction(Sequence::create(FadeIn::create(0.2f),
                                                      MoveTo::create(1.0f,starToPosition),
                                                      FadeOut::create(0.01f),
                                                      cont->runAction(Sequence::create(ScaleTo::create(0.1f,1.1),
                                                                                       ScaleTo::create(0.3f,1.0), nullptr)),
                                                      nullptr));
                    }
                }
            });
            ssb->setVisible(false);
            this->addChild(ssb,zOrder);
            o->s=ss;
            o->b=ssb;
            o->obj=it;
            o->zOrder=zOrder;
            starList.emplace_back(o);
        }
        zOrder--;
    }

    audioTime = Label::createWithTTF(labelConfig, "");
    audioTime->setPosition(Vec2(150.0f, 200.0f));
    this->addChild(audioTime,3);

    isAuto=XMLConfigUtil::getInstance()->ReadConfig("AutoMode");

    effectVoice=XMLConfigUtil::getInstance()->ReadConfig("EffectVoice")*0.01f;
    if(XMLConfigUtil::getInstance()->ReadConfig("GlobalOffset")==0|| XMLConfigUtil::getInstance()->ReadConfig("PreRender")==0){
        globaloffset=0.001;
        prerender=0.01;
    } else{
        globaloffset=1.0f/XMLConfigUtil::getInstance()->ReadConfig("GlobalOffset");
        prerender=1.0f/XMLConfigUtil::getInstance()->ReadConfig("PreRender");
    }

    cont=Sprite::create("scene/gamelayer/cont.png");
    cont->setPosition(cont->getContentSize().width/2.0f,visibleSize.height-nextBar->getContentSize().height-cont->getContentSize().height/2.0f);
    this->addChild(cont,65535);

    score= Label::createWithTTF(labelConfig, to_string(compObj)+" / "+to_string(totalObj));
    score->setPosition(Vec2(cont->getContentSize().width+100,visibleSize.height-nextBar->getContentSize().height-cont->getContentSize().height/2.0f));
    this->addChild(score,3);

    starToPosition=Vec2(cont->getContentSize().width/2.0f,visibleSize.height-nextBar->getContentSize().height-cont->getContentSize().height/2.0f);

    delete fileData;
    return true;
}

void GameLayer::AudioCallback(int audio,const string &s){
    unscheduleUpdate();
    double score = 0.0;
    double total = 0.0;
    double temp = 0.0;
    for(auto it :hitOffsetList){
        it = std::abs(it);
        if(it<0.1 && it>=0){
            temp=1*1;
        } else if(it<1 && it>=0.1){
            temp=1*0.5;
        } else if(it >=1){
            temp=1*0;
        }
        total += temp;
    }
    score = total/astroid->astroidObject.size();
    RWCache::getInstance()->WriteScoreCache(score);
    sm->ToScoreScene();
}

void GameLayer::PreloadCallback(bool s){
    if(s){
//        playerStartButton->setEnabled(true);
//        playerStartButton->setVisible(true);
        iAudioID = AudioEngine::play2d(sAudioPath, false,XMLConfigUtil::getInstance()->ReadConfig("Voice")*0.01f);
        scheduleUpdate();
        funcMenu->setVisible(true);
        AudioEngine::setFinishCallback(iAudioID,CC_CALLBACK_2(GameLayer::AudioCallback,this));
    }
}

void GameLayer::PlayButtonCallback(Ref *pSender, ui::Widget::TouchEventType type){
    if(type == ui::Widget::TouchEventType::BEGAN){
        playerStartButton->setEnabled(false);
        playerStartButton->setVisible(false);
        sm->gameScene->SetBackgroundColor(Color3B(140,140,140));
        nextBarOver1->runAction(RepeatForever::create(RotateBy::create(5.0f,360.0f)));
        nextBarOver2->runAction(RepeatForever::create(RotateBy::create(5.0f,360.0f)));
        nextBarOver3->runAction(RepeatForever::create(RotateBy::create(5.0f,360.0f)));
        AudioEngine::preload(sAudioPath,CC_CALLBACK_1(GameLayer::PreloadCallback,this));
    }
}

void GameLayer::update(float delta) {
    ticktime += delta;

    if(flag){
        objtemp = starList.at(index);
        distance = objtemp->obj->getDistance();
        offset=objtemp->obj->getOffset()/1000.0f;
        if(objtemp->type == AstroidObjectEnums::TwinkleStar){
            temp_x=objtemp->x;
            temp_y=objtemp->y;
            temp_type=AstroidObjectEnums::TwinkleStar;
        } else{
            temp_x=objtemp->x;
            isTooHeight=objtemp->isTooHeight;
            temp_y=objtemp->y;
            temp_type=AstroidObjectEnums::StreamStar;
        }
        flag=false;
    }

    if(size){
        nextBar->setPercent((offset - ticktime)*100);
        //audioTime->setString(to_string(offset - ticktime));
        if( offset - ticktime <= globaloffset){
            if(isAuto){
                hitOffsetList.emplace_back(offset - ticktime);
            }

            if(temp_type == AstroidObjectEnums::StreamStar){
                if(isTooHeight){
                    skeletonNode->setPosition(Vec2(temp_x-50,jpy));
                    skeletonNode->stopAllActions();
                    skeletonNode->setAnimation(0,"catch",false);
                    skeletonNode->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(topheight/1000.0f,Vec2(temp_x-50,topheight - 50))),
                                                             EaseSineIn::create(MoveTo::create(topheight/1000.0f,Vec2(temp_x-50,jpy))),nullptr));
                    if(isAuto){
                        AudioEngine::play2d("scene/gamelayer/hit.mp3", false, effectVoice);
                        auto sb = Sprite::create("scene/gamelayer/sssb.png");
                        sb->setPosition(temp_x,topheight);
                        sb->setScale(0.6);
                        this->addChild(sb,5);
                        sb->runAction(Spawn::create(ScaleTo::create(1.0f,1.2f),
                                                    FadeOut::create(1.0f),
                                                    nullptr));
                        auto s = Sprite::create("scene/gamelayer/fs.png");
                        s->setPosition(temp_x,topheight);
                        this->addChild(s,5);
                        s->runAction(Sequence::create(FadeIn::create(0.2f),
                                                      MoveTo::create(1.0f,starToPosition),
                                                      FadeOut::create(0.01f),
                                                      cont->runAction(Sequence::create(ScaleTo::create(0.1f,1.1),
                                                                                       ScaleTo::create(0.3f,1.0), nullptr)),
                                                      nullptr));
                        compObj = hitOffsetList.size();
                        score->setString(to_string(compObj)+" / "+to_string(totalObj));
                    }
                } else{
                    skeletonNode->setPosition(Vec2(temp_x-50,jpy));
                    skeletonNode->stopAllActions();
                    skeletonNode->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(temp_y/1000.0f,Vec2(temp_x-50,temp_y - 50))),
                                                             EaseSineIn::create(MoveTo::create(temp_y/1000.0f,Vec2(temp_x-50,jpy))),nullptr));
                    skeletonNode->setAnimation(0,"catch",false);
                    if(isAuto){
                        AudioEngine::play2d("scene/gamelayer/hit.mp3", false, effectVoice);
                        auto sb = Sprite::create("scene/gamelayer/sssb.png");
                        sb->setPosition(temp_x,temp_y);
                        sb->setScale(0.6);
                        this->addChild(sb,5);
                        sb->runAction(Spawn::create(ScaleTo::create(1.0f,1.2f),
                                                    FadeOut::create(1.0f),
                                                    nullptr));
                        auto s = Sprite::create("scene/gamelayer/fs.png");
                        s->setPosition(temp_x,temp_y);
                        this->addChild(s,5);
                        s->runAction(Sequence::create(FadeIn::create(0.2f),
                                                      MoveTo::create(1.0f,starToPosition),
                                                      FadeOut::create(0.01f),
                                                      cont->runAction(Sequence::create(ScaleTo::create(0.1f,1.1),
                                                                                       ScaleTo::create(0.3f,1.0), nullptr)),
                                                      nullptr));

                        compObj = hitOffsetList.size();
                        score->setString(to_string(compObj)+" / "+to_string(totalObj));
                    }
                }
            } else{
                skeletonNode->stopAllActions();
                skeletonNode->setAnimation(0,"catch",false);
                skeletonNode->setPosition(Vec2(temp_x-50,jpy));
                if(isAuto){
                    AudioEngine::play2d("scene/gamelayer/hit.mp3", false, effectVoice);
                    auto sb = Sprite::create("scene/gamelayer/tssb.png");
                    sb->setScale(0.6);
                    sb->setPosition(temp_x,temp_y);
                    this->addChild(sb,5);
                    sb->runAction(Spawn::create(ScaleTo::create(1.0f,1.2f),
                                                FadeOut::create(1.0f),
                                                nullptr));
                    auto s = Sprite::create("scene/gamelayer/fs.png");
                    s->setPosition(temp_x,temp_y);
                    this->addChild(s,5);
                    s->runAction(Sequence::create(FadeIn::create(0.2f),
                                                  MoveTo::create(1.0f,starToPosition),
                                                  FadeOut::create(0.01f),
                                                  cont->runAction(Sequence::create(ScaleTo::create(0.1f,1.1),
                                                                                   ScaleTo::create(0.3f,1.0), nullptr)),
                                                  nullptr));
                    compObj = hitOffsetList.size();
                    score->setString(to_string(compObj)+" / "+to_string(totalObj));
                }
            }
            if(distance == -1){
                flag = false;
                size = false;
                skeletonNode->stopAllActions();
                skeletonNode->setAnimation(0,"cheer", true);
                //skeletonNode->setAnimation(0,"mark",true);
            } else{
                flag=true;
            }
            index++;
        }
    }

    for(auto it : starList){
        if(it->obj->getOffset() / 1000.0f - ticktime <= 0.4 && it->obj->getOffset() / 1000.0f - ticktime >=0){
            if(it->type == AstroidObjectEnums::TwinkleStar){
                it->s->setVisible(true);
                it->b->setVisible(true);
                if(isAuto){
                    it->b->setEnabled(false);
                }
                it->s->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2f,0.8f),FadeIn::create(0.2f),
                                                                nullptr),FadeOut::create(0.2f), nullptr));
                it->b->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2f,0.8f),FadeIn::create(0.2f),
                                                                nullptr),FadeOut::create(0.2f), nullptr));
            } else{
                it->s->setVisible(true);
                it->b->setVisible(true);
                if(isAuto){
                    it->b->setEnabled(false);
                }
                it->s->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2,0.8f),FadeIn::create(0.2f),
                                                                nullptr),FadeOut::create(0.2f), nullptr));
                it->b->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2f,0.8f),FadeIn::create(0.2f),
                                                                nullptr),FadeOut::create(0.2f), nullptr));
            }
        }
    }

    for(auto it : starList){
        if(it->obj->getOffset() / 1000.0f - ticktime >= -0.5 && it->obj->getOffset() / 1000.0f - ticktime <=-0.3){
            if(it->type == AstroidObjectEnums::TwinkleStar){
                it->s->setVisible(false);
                it->b->setVisible(false);
            } else{
                it->s->setVisible(false);
                it->b->setVisible(false);

            }
        }
    }
}


void GameLayer::StopScene(Ref * pSender) {
    AudioEngine::pause(iAudioID);
    pause();
    sm->ToStopLayer(iAudioID);
}

int GameLayer::getIAudioId() const {
    return iAudioID;
}

