//
// Created by qq454 on 2022/03/24.
//

#include "ListViewLayer.h"
#include "cocos/ui/UIListView.h"
#include "ui/UIImageView.h"
#include "service/GetListData.h"
#include "AudioEngine.h"
#include "util/RWCache.h"
#include "util/XMLConfigUtil.h"
#include "view/MapListScene.h"
#include "StartMenuLayer.h"

USING_NS_CC;
using namespace cocos2d::ui;

Layer *ListViewLayer::createScene() {
    return ListViewLayer::create();
}

bool ListViewLayer::init() {
    if(!Layer::init()){
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    pListView = ListView::create();
    beatmapList = GetListData::DoGetListData(beatmapList);
    pListView->setOpacity(60);
    pListView->setBackGroundColor(Color3B(200,200,200));
    pListView->setContentSize(Size(visibleSize.width / 2,visibleSize.height));
    pListView->setPosition(Vec2::ZERO);
    pListView->setBounceEnabled(true);
    pListView->setTouchEnabled(true);
    pListView->setDirection(ScrollView::Direction::VERTICAL);
    pListView->addEventListener(CC_CALLBACK_2(ListViewLayer::ListViewCallback, this));

    massage = Sprite::create("scene/listviewlayer/massage.png");
    massage->setScale(SceneManager::AutoScale(visibleSize,massage) * 0.8f);
    massage->setPosition(Size(visibleSize.width - massage->getContentSize().width / 2,visibleSize.height - massage->getContentSize().height / 2));
    this->addChild(massage,1);
    massage->setVisible(false);
    ObjiceAddToList();
    this->addChild(pListView,1);
    return true;
}

void ListViewLayer::ObjiceAddToList() {

    for(auto it :beatmapList){
        auto layout = Layout::create();
        layout->setContentSize(Size(Director::getInstance()->getVisibleSize().width / 2,150));
        layout->setName(it->beatmapInfo->getSPath());
        layout->setBackGroundImage("scene/listviewlayer/listitem.png");
        layout->setPosition(Vec2(100,100));

        auto imageView = ImageView::create(SceneManager::AutoPathToSTDPath(it->beatmapInfo->getSPath(),it->beatmapInfo->getSBackground()));
        imageView->setContentSize(Size(178,100));
        imageView->ignoreContentAdaptWithSize(false);
        imageView->setPosition(Vec2(90,75));
        imageView->setTouchEnabled(true);
        layout->addChild(imageView,3);

        TTFConfig labelConfig1;
        labelConfig1.fontFilePath ="fonts/arial.ttf";
        labelConfig1.fontSize = 20;
        labelConfig1.glyphs = GlyphCollection::DYNAMIC;
        labelConfig1.bold= true;

        auto titleLabel = Label::createWithTTF(labelConfig1,"Title: " + it->song->getSEnTitle());
        titleLabel->setAnchorPoint(Vec2::ZERO);
        titleLabel->setDimensions(500.0f ,50.0f);
        titleLabel->setPosition(Vec2(185,50));
        imageView->addChild(titleLabel,3);

        TTFConfig labelConfig2;
        labelConfig2.fontFilePath ="fonts/arial.ttf";
        labelConfig2.fontSize = 15;
        labelConfig2.glyphs = GlyphCollection::DYNAMIC;
        labelConfig2.bold= true;

        auto difficultyLabel = Label::createWithTTF(labelConfig2,"Difficulty: " + it->beatmapInfo->getSDifficulty());
        difficultyLabel->setAnchorPoint(Vec2::ZERO);
        difficultyLabel->setDimensions(500.0f ,50.0f);
        difficultyLabel->setPosition(Vec2(185,0));
        imageView->addChild(difficultyLabel,3);

        pListView->addChild(layout,2);

        auto *f=new FileData();
        RWCache::getInstance()->ReadPathCache(f);
        if(it->beatmapInfo->getSPath() == f->getSPath()){
            pListView->setCurSelectedIndex(pListView->getIndex(layout));
            layout->setBackGroundImage("scene/listviewlayer/listitem2.png");
            forwardIndex=pListView->getIndex(layout);
        }
        delete f;
    }
}

void ListViewLayer::ListViewCallback(Ref* pSender,ListView::EventType type){
    if(type == ListView::EventType::ON_SELECTED_ITEM_START){
        massage->removeAllChildren();
        auto view = dynamic_cast<ListView*> (pSender);
        auto layout = dynamic_cast<Layout*> (view->getItem(view->getCurSelectedIndex()));
        auto flayout = dynamic_cast<Layout*>(view->getItem(forwardIndex));
        flayout->setBackGroundImage("scene/listviewlayer/listitem.png");
        layout->setBackGroundImage("scene/listviewlayer/listitem2.png");
        forwardIndex=view->getCurSelectedIndex();
        std::string s = layout->getName();
        auto *beatmap = new Beatmap();
        OSUFileReadUtil::getInstance()->setAttributes(beatmap,s);

        string audioPath = SceneManager::AutoPathToSTDPath(s,beatmap->song->getSAudioFilename());
        AudioEngine::uncacheAll();
        AudioEngine::preload(audioPath);

        auto *f = new FileData();
        f->setSPath(beatmap->beatmapInfo->getSPath());
        f->setSAudioFilePath(beatmap->song->getSAudioFilename());
        f->setSBackGroundPath(beatmap->beatmapInfo->getSBackground());
        backgroundAudioID = AudioEngine::play2d(audioPath, true,XMLConfigUtil::getInstance()->ReadConfig("Voice")*0.01f);
        RWCache::getInstance()->WritePathCache(f);

        string backgroundPath = SceneManager::AutoPathToSTDPath(s,beatmap->beatmapInfo->getSBackground());
        sm->mapListScene->ChangeBackground(backgroundPath);
        sm->startMenuScene->ChangeBackground(backgroundPath);
        auto *startMenuLayer = dynamic_cast<StartMenuLayer*>(sm->startMenuScene->getChildByName("startMenuLayer"));
        startMenuLayer->ChangeTitleLabel(beatmap->song->getSEnArtist()+ " - " + beatmap->song->getSEnTitle());
        delete f;
    }
}

int ListViewLayer::getBackgroundAudioId() const {
    return backgroundAudioID;
}

