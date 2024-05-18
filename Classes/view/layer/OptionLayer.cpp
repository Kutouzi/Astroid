//
// Created by qq454 on 2022/03/23.
//

#include "OptionLayer.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "view/SceneManager.h"
#include "util/XMLConfigUtil.h"

using namespace cocos2d::ui;
USING_NS_CC;

bool OptionLayer::init() {
    if ( !Layer::init() ){
        return false;
    }
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("scene/optionlayer/optionlayer.png");
    background->setScale(SceneManager::AutoScale(visibleSize,background) * 0.8f);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);

    auto slider = Slider::create();
    slider->loadBarTexture("scene/optionlayer/slider.png");
    slider->loadSlidBallTextures("scene/optionlayer/sliderbuttonnormal.png",
                                 "scene/optionlayer/sliderbuttoning.png",
                                 "scene/optionlayer/sliderbuttonfalse.png");
    slider->loadProgressBarTexture("scene/optionlayer/sliderover.png");
    slider->setPosition(Vec2(500.0f,600.0f));
    slider->setScale(0.5f);
    slider->setSizePercent(Vec2(0,100));
    int d = XMLConfigUtil::getInstance()->ReadConfig("Voice");
    slider->setPercent(d);
    background->addChild(slider,12);
    slider->addEventListener(CC_CALLBACK_2(OptionLayer::SliderCallback,this));

    auto voice = ImageView::create("scene/optionlayer/voice.png");
    voice->setPosition(Vec2(150.0f,600.0f));
    background->addChild(voice,11);

    auto slider2 = Slider::create();
    slider2->loadBarTexture("scene/optionlayer/slider.png");
    slider2->loadSlidBallTextures("scene/optionlayer/sliderbuttonnormal.png",
                                 "scene/optionlayer/sliderbuttoning.png",
                                 "scene/optionlayer/sliderbuttonfalse.png");
    slider2->loadProgressBarTexture("scene/optionlayer/sliderover.png");
    slider2->setPosition(Vec2(500.0f,500.0f));
    slider2->setScale(0.5f);
    slider2->setSizePercent(Vec2(0,100));
    int d2 = XMLConfigUtil::getInstance()->ReadConfig("EffectVoice");
    slider2->setPercent(d2);
    background->addChild(slider2,12);
    slider2->addEventListener(CC_CALLBACK_2(OptionLayer::SliderCallback2,this));

    auto effectVoice = ImageView::create("scene/optionlayer/effectvoice.png");
    effectVoice->setPosition(Vec2(150.0f,500.0f));
    background->addChild(effectVoice,11);

    auto textField2 = TextField::create("","fonts/arial.ttf",30);
    textField2->setString(to_string(XMLConfigUtil::getInstance()->ReadConfig("PreRender")));
    textField2->setPosition(Vec2(400.0f,400.0f));
    textField2->setColor(Color3B(100,100,100));
    textField2->setMaxLengthEnabled(true);
    textField2->setCursorEnabled(true);
    textField2->setMaxLength(5);
    textField2->addEventListener(CC_CALLBACK_2(OptionLayer::TextFieldCallback2,this));
    background->addChild(textField2,12);

    auto labelbg = ImageView::create("scene/optionlayer/labelbg.png");
    labelbg->setPosition(Vec2(400.0f,400.0f));
    labelbg->setScale(0.6);
    background->addChild(labelbg,11);

    auto prerender = ImageView::create("scene/optionlayer/prerender.png");
    prerender->setPosition(Vec2(150.0f,400.0f));
    background->addChild(prerender,11);

    auto textField = TextField::create("","fonts/arial.ttf",30);
    textField->setPosition(Vec2(400.0f,300.0f));
    textField->setColor(Color3B(100,100,100));
    textField->setMaxLengthEnabled(true);
    textField->setMaxLength(5);
    textField->setCursorEnabled(true);
    textField->addEventListener(CC_CALLBACK_2(OptionLayer::TextFieldCallback,this));
    textField->setString(to_string(XMLConfigUtil::getInstance()->ReadConfig("GlobalOffset")));
    background->addChild(textField,12);

    auto labelbg1 = ImageView::create("scene/optionlayer/labelbg.png");
    labelbg1->setPosition(Vec2(400.0f,300.0f));
    labelbg1->setScale(0.6);
    background->addChild(labelbg1,11);

    auto offset = ImageView::create("scene/optionlayer/offset.png");
    offset->setPosition(Vec2(150.0f,300.0f));
    background->addChild(offset,11);

    auto checkbox = CheckBox::create("scene/optionlayer/select.png",
                                     "scene/optionlayer/selectp.png",
                                     "scene/optionlayer/selected.png",
                                     "scene/optionlayer/select.png",
                                     "scene/optionlayer/select.png");
    checkbox->setSelected(XMLConfigUtil::getInstance()->ReadConfig("AutoMode"));
    checkbox->addEventListener(CC_CALLBACK_2(OptionLayer::SelectCallback,this));
    checkbox->setScale(0.7);
    checkbox->setPosition(Vec2(400.0f,200.0f));
    background->addChild(checkbox,12);

    auto autoplay = ImageView::create("scene/optionlayer/auto.png");
    autoplay->setPosition(Vec2(150.0f,200.0f));
    background->addChild(autoplay,11);

    auto backButton = MenuItemImage::create(
            "scene/optionlayer/backbutton.png",
            "scene/optionlayer/backbutton.png",
            CC_CALLBACK_1(OptionLayer::BackCallback, this));
    backButton->setPosition(Vec2(600.0f, 100.0f));
    backButton->setScale(0.8f);

    auto funcMenu = Menu::create(backButton, NULL);
    funcMenu->setPosition(Vec2::ZERO);
    background->addChild(funcMenu,11);

    return true;
}
void OptionLayer::SliderCallback(Ref* pSender,Slider::EventType type){
    auto * slider = dynamic_cast<Slider*>(pSender);
    for (int i = 0; i <= 65535; i++) {
        AudioEngine::setVolume(i,slider->getPercent() / 100.0f);
    }
    if(type == Slider::EventType::ON_SLIDEBALL_UP){
        string s = "Voice";
        string l = to_string(slider->getPercent());
        XMLConfigUtil::getInstance()->UpdateConfig(s, l);
    }
}

void OptionLayer::SliderCallback2(Ref* pSender,Slider::EventType type){
    auto * slider = dynamic_cast<Slider*>(pSender);
    if(type == Slider::EventType::ON_SLIDEBALL_UP){
        string s = "EffectVoice";
        string l = to_string(slider->getPercent());
        XMLConfigUtil::getInstance()->UpdateConfig(s, l);
    }
}

void OptionLayer::TextFieldCallback(Ref* pSender,TextField::EventType type){
    auto * textField = dynamic_cast<TextField*>(pSender);
    if(type == TextField::EventType::DETACH_WITH_IME){
        string s = "GlobalOffset";
        string l = textField->getString();
        string t = to_string(ToNum(l));
        if(ToNum(l)!=0){
            XMLConfigUtil::getInstance()->UpdateConfig(s, t);
            textField->setString(to_string(ToNum(l)));
        } else{
            textField->setString("1000");
        }
    }
}

void OptionLayer::TextFieldCallback2(Ref* pSender,TextField::EventType type){
    auto * textField = dynamic_cast<TextField*>(pSender);
    if(type == TextField::EventType::DETACH_WITH_IME){
        string s = "PreRender";
        string l = textField->getString();
        string t = to_string(ToNum(l));
        if(ToNum(l)!=0){
            XMLConfigUtil::getInstance()->UpdateConfig(s, t);
            textField->setString(to_string(ToNum(l)));
        } else{
            textField->setString("100");
        }
    }
}

OptionLayer* OptionLayer::createScene()
{
    return OptionLayer::create();
}

void OptionLayer::BackCallback(cocos2d::Ref *pSender) {
    sm->ToStartMenuScene();
}

void OptionLayer::SelectCallback(Ref* sender, CheckBox::EventType type){
    if(type==CheckBox::EventType::SELECTED){
        string s = "AutoMode";
        string l = "1";
        XMLConfigUtil::getInstance()->UpdateConfig(s, l);
    }
    if(type==CheckBox::EventType::UNSELECTED){
        string s = "AutoMode";
        string l = "0";
        XMLConfigUtil::getInstance()->UpdateConfig(s, l);
    }
}

unsigned int OptionLayer::ToNum(const string& str){
    stringstream sin(str);
    unsigned int d;
    if(sin >> d){
        cout<<d<<endl;
        return d;
    }
    return 100;
}

