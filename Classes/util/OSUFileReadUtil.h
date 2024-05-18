//
// Created by qq454 on 2022/03/07.
//

#ifndef ASTROID_OSUFILEREADUTIL_H
#define ASTROID_OSUFILEREADUTIL_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <codecvt>
#include "entity/Beatmap.h"

using namespace std;

class OSUFileReadUtil {
private:
    OSUFileReadUtil() = default;
public:
    static OSUFileReadUtil *getInstance() {
        return new OSUFileReadUtil();
    }

    /**
     * @details 读取osu文件并且创建beatmap对象
     * @param sPath 传入osu文件路径（包含文件名的）
     * @return 读取并且创建成功为true，否则false
     */
    bool ReadOSUFile(std::string &sPath,Beatmap *&beatmap) {
        try {
            beatmap->beatmapInfo->setSPath(sPath);
            setAttributes(beatmap, sPath);
            setTimingControlPoint(beatmap, sPath);
            setOsuHitObjects(beatmap,sPath);
            return true;
        } catch (std::bad_exception &e) {
            std::cout << "Cant read file" << std::endl;
            return false;
        }
    }

    /**
     * @details 遍历osu文件的元数据内容并且为对象设置值
     * @param beatmap 一个对象
     * @param sPath osu文件路径
     */
    void setAttributes(Beatmap *&beatmap, std::string &sPath) {
        beatmap->beatmapInfo->setSPath(sPath);
        std::ifstream file(sPath);
        std::string line;
        const char *pos = ":";
        const char *txj = " ";
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        while (std::getline(file, line)) {
            if (line.find("AudioFilename:") != std::string::npos) {
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                line.erase(0, line.find_first_not_of(txj));
                beatmap->song->setSAudioFilename(line);
            }
            else if(line.find("AudioLeadIn:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                line.erase(0, line.find_first_not_of(txj));
                beatmap->beatmapInfo->setDAudioLeadIn(StringToDouble(line));
            }
            else if(line.find("PreviewTime:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                line.erase(0, line.find_first_not_of(txj));
                beatmap->beatmapInfo->setDAudioLeadIn(StringToInt(line));
            }
            if(line.find("Title:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->song->setSEnTitle(line);
            }
            else if(line.find("TitleUnicode:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->song->setSOrgTitle(conv.from_bytes(line));
            }
            else if(line.find("Artist:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->song->setSEnArtist(line);
            }
            else if(line.find("ArtistUnicode:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                std::string narrowStr = conv.to_bytes(conv.from_bytes(line));
                beatmap->song->setSOrgArtist(conv.from_bytes(line));
            }
            else if(line.find("Creator:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->song->setSCreator(line);
            }
            else if(line.find("Version:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->beatmapInfo->setSDifficulty(line);
            }
            else if(line.find("BeatmapID:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                stringstream ss;
                beatmap->beatmapInfo->setIBeatmapId(StringToInt(line));
            }
            else if(line.find("BeatmapSetID:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->beatmapInfo->setIBeatmapSetId(StringToInt(line));
            }
            else if(line.find("SliderMultiplier:") != std::string::npos){
                line = line.substr(line.find(pos));
                line.erase(0, line.find_first_not_of(pos));
                beatmap->beatmapInfo->setFMultiplier(StringToDouble(line));
            }
            if(line.find(".jpg") != std::string::npos || line.find(".png") != std::string::npos){
                std::regex reg(R"("{1}.*\.{1}.*"{1})");
                string::const_iterator iterStart = line.begin();
                string::const_iterator iterEnd = line.end();
                std::smatch result;
                regex_search(iterStart, iterEnd, result, reg);
                string s = result[0];
                const char *const pdj = R"(")";
                int index = 0;
                while ((index = s.find(pdj, index)) != string::npos){
                    s.erase(index, 1);
                }
                beatmap->beatmapInfo->setSBackground(s);
            }
        }
        file.close();
    }
    /**
     * @details 遍历读取osu文件的时间控制点内容
     * @param beatmap 一个对象
     * @param sPath osu文件路径
     */
    void setTimingControlPoint(Beatmap *&beatmap, std::string &sPath){
        std::ifstream file(sPath);
        std::string line;
        while (getline(file,line)) {
            if (line.find("[TimingPoints]") != std::string::npos) {
                while (getline(file,line)){
                    if(!line.empty()){
                        vector<std::string> list=Split(line,",");
                        auto *t = new TimingControlPoint();
                        t->setITime(StringToInt(list[0]));
                        t->setDBeatLength(StringToDouble(list[1]));
                        t->setIMeter(StringToInt(list[2]));
                        t->setBUninherited(StringToInt(list[6]));
                        beatmap->timeControlPoint.emplace_back(t);
                    } else{
                        file.close();
                        return;
                    }
                }
            }
            if(file.eof()){
                break;
            }
        }
        file.close();
    }
    /**
     * @details 遍历读取osu文件的时间控制点内容
     * @param beatmap 一个对象
     * @param sPath osu文件路径
     */
    void setOsuHitObjects(Beatmap *&beatmap, std::string &sPath){
        std::ifstream file(sPath);
        std::string line;
        while (getline(file,line)) {
            if (line.find("[HitObjects]") != std::string::npos) {
                while (getline(file,line)){
                    if(!line.empty()){
                        vector<std::string> list=Split(line,",");
                        auto o =new OsuHitObjects();
                        o->setX(StringToInt(list[0]));
                        o->setY(StringToInt(list[1]));
                        o->setOffset(StringToInt(list[2]));
                        if(StringToInt(list[3]) == 1 || StringToInt(list[3]) == 5){
                            o->setEObjectType(OsuObjectEnums::HitCircle);
                            o->setEx(o->getX());
                            o->setEy(o->getX());
                        } else if (StringToInt(list[3]) == 2 || StringToInt(list[3]) == 6){
                            o->setEObjectType(OsuObjectEnums::Slider);
                            o->setCount(StringToInt(list[6]));
                            o->setLength(StringToDouble(list[7]));
                            vector<std::string>  v = Split(list[5],"|");
                            vector<string> endPos = Split(v.at(v.size()-1),":");
                            o->setEx(StringToInt(endPos.at(0)));
                            o->setEy(StringToInt(endPos.at(1)));

                        } else if(StringToInt(list[3]) == 12){
                            o->setEObjectType(OsuObjectEnums::Spinner);
                            o->setEx(o->getX());
                            o->setEy(o->getX());
                            o->setEndoffset(StringToInt(list[5]));
                        }
                        beatmap->osuHitObjects.push_back(o);
                    }else{
                        file.close();
                        return;
                    }
                }
            }
            if(file.eof()){
                break;
            }
        }
        file.close();
    }
    /**
     * @details 用于切分字符串函数
     * @param str 传入的字符串
     * @param pattern 传入的切分字符
     * @return 一个字符串列表
     */
    static std::vector<std::string> Split(const std::string &str, const std::string &pattern) {
        char *strc = new char[strlen(str.c_str()) + 1];
        strcpy(strc, str.c_str());
        std::vector<std::string> resultVec;
        char *tmpStr = strtok(strc, pattern.c_str());
        while (tmpStr != nullptr) {
            resultVec.emplace_back(tmpStr);
            tmpStr = strtok(nullptr, pattern.c_str());
        }
        delete[] strc;
        return resultVec;
    }
    /**
     * @details 将字符串转换为int
     * @param s 传入字符串
     * @return 一个int
     */
    static int StringToInt(std::string &s){
        stringstream ss;
        int n;
        ss<<s;
        ss>>n;
        return n;
    }

    /**
     * @details 将字符串转换为double
     * @param s 传入字符串
     * @return 一个double
     */
    static double StringToDouble(std::string &s){
        stringstream ss;
        double n;
        ss<<s;
        ss>>n;
        return n;
    }
};


#endif //ASTROID_OSUFILEREADUTIL_H
