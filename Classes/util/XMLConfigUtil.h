//
// Created by qq454 on 2022/02/23.
//

#ifndef ASTROID_XMLCONFIGUTIL_H
#define ASTROID_XMLCONFIGUTIL_H

#include <exception>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "OSUFileReadUtil.h"

class XMLConfigUtil {
public:
    static XMLConfigUtil *getInstance() {
        return new XMLConfigUtil();
    }
    /**
     * 创建初始的xml文件
     * @return 非0失败，返回0成功
     */
    int InitConfig() {
            try {
                auto *doc = new tinyxml2::XMLDocument;
                if(doc->LoadFile(XMLPath.c_str())!=0){
                    auto root=doc->NewElement("GameConfig");
                    doc->InsertEndChild(root);

                    auto pVoiceNode  = doc->NewElement("Voice");
                    pVoiceNode->SetAttribute("Value",50);
                    root->InsertEndChild(pVoiceNode);

                    auto pGlobalOffsetNode = doc->NewElement("GlobalOffset");
                    pGlobalOffsetNode->SetAttribute("Value",1000);
                    root->InsertEndChild(pGlobalOffsetNode);

                    auto pEffectVoiceNode  = doc->NewElement("EffectVoice");
                    pEffectVoiceNode->SetAttribute("Value",100);
                    root->InsertEndChild(pEffectVoiceNode);

                    auto pPreRenderNode  = doc->NewElement("PreRender");
                    pPreRenderNode->SetAttribute("Value",100);
                    root->InsertEndChild(pPreRenderNode);

                    auto pAutoModeNode  = doc->NewElement("AutoMode");
                    pAutoModeNode->SetAttribute("Value",0);
                    root->InsertEndChild(pAutoModeNode);

                    int writeOK = doc->SaveFile(XMLPath.c_str());
                    /*释放对象*/
                    delete doc;
                    return writeOK;
                }
            } catch (std::bad_exception e) {
                std::cout
                        << "Cant creat GameConfig.xml, please check if you have file read and write permissions and try again."
                        << std::endl;
                return 1;
            }
        return 0;
    }

    /**
     * @details
     * 用于读取GameConfig.xml文件，且会检查是否有创建
     * @return
     * 取失败返回nullptr,成功返回对象指针
     */
private:
    tinyxml2::XMLDocument * ReturnDoc() {
        auto *doc = new tinyxml2::XMLDocument();
        if (doc->LoadFile(XMLPath.c_str())!=0) {
            return nullptr;
        } else{
            return doc;
        }
    }

public:
    /**
     * @details 用于写入新的数据，如果没有GameConfig.xml会先创建
     * @param sNode 需要修改的项目名
     * @param sValue 需要修改的项目值
     * @return 返回true修改成功，否则失败
     */
    bool UpdateConfig(std::string &sNode, std::string &sValue) {
        tinyxml2::XMLDocument *pGameConfig = ReturnDoc();
        if (pGameConfig != nullptr) {
            tinyxml2::XMLElement* node=pGameConfig->RootElement()->FirstChildElement();
            while(node){
                if(node->Name() == sNode){
                    node->SetAttribute("Value",sValue.c_str());
                    int writeOK = pGameConfig->SaveFile(XMLPath.c_str());
                    return writeOK;
                }
                node=node->NextSiblingElement();
            }
            return false;
        }
        return false;
    }
    int ReadConfig(const std::string& sNode){
        tinyxml2::XMLDocument *pGameConfig = ReturnDoc();
        tinyxml2::XMLElement* node = pGameConfig->RootElement()->FirstChildElement();
        while (node){
            if(node->Name() == sNode){
                std::string s = node->FirstAttribute()->Value();
                return OSUFileReadUtil::StringToInt(s);
            }
            node = node->NextSiblingElement();
        }
        return 0;
    }
private:
    XMLConfigUtil() = default;

#ifdef WIN32
    std::string XMLPath = FileUtils::getInstance()->getSearchPaths().at(0) + "/config/GameConfig.xml";
#else
    std::string XMLPath = "/storage/emulated/0/Download/Resources/config/GameConfig.xml";
#endif
};


#endif //ASTROID_XMLCONFIGUTIL_H
