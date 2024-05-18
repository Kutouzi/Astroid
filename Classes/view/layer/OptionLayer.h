//
// Created by qq454 on 2022/03/23.
//

#ifndef ASTROID_OPTIONLAYER_H
#define ASTROID_OPTIONLAYER_H

#include <string>
#include "cocos2d.h"
#include "view/SceneManager.h"
#include "ui/UISlider.h"
#include "ui/UITextField.h"
#include "ui/UICheckBox.h"

using namespace cocos2d::ui;

class OptionLayer : public cocos2d::Layer{
public:
    SceneManager *sm;
    int backgroundAudioID = 0;
    static OptionLayer* createScene();
    void SliderCallback(cocos2d::Ref* pSender,Slider::EventType type);
    void BackCallback(cocos2d::Ref* pSender);
    virtual bool init();
    CREATE_FUNC(OptionLayer);
    void SliderCallback2(Ref *pSender, Slider::EventType type);

    void TextFieldCallback(Ref *pSender, cocos2d::ui::TextField::EventType type);

    void TextFieldCallback2(Ref *pSender, TextField::EventType type);

    unsigned int ToNum(const std::string &str);

    void SelectCallback(Ref *sender, CheckBox::EventType type);
};


#endif //ASTROID_OPTIONLAYER_H
