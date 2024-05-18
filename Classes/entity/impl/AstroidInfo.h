//
// Created by qq454 on 2022/03/18.
//

#ifndef ASTROID_ASTROIDINFO_H
#define ASTROID_ASTROIDINFO_H


#include <string>
#include "Song.h"

class AstroidInfo {
private:
    /**
     * @details 歌曲编号
     */
    int iID = 0;
    /**
     * @details 歌曲信息的对象
     */
    Song *song;
    /**
     * @details 难度名
     */
    std::string sDifficulty;
    /**
     * @details 铺面路径
     */
    string sPath;
    /**
     * @details 播放歌曲前的引导时间
     */
    double dAudioLeadIn = 0.0f;
    /**
     * @details 歌曲预览时间
     */
    int iPreviewTime = -1;
    /**
     * @details 目录下歌曲背景图片名称
     */
    string sBackground;
public:
    explicit AstroidInfo(Song *song){
        this->song=song;
    }
    int getIid() const {
        return iID;
    }

    void setIid(int iId) {
        iID = iId;
    }

    const string &getSDifficulty() const {
        return sDifficulty;
    }

    void setSDifficulty(const string &sDifficulty) {
        AstroidInfo::sDifficulty = sDifficulty;
    }

    const string &getSPath() const {
        return sPath;
    }

    void setSPath(const string &sPath) {
        AstroidInfo::sPath = sPath;
    }

    double getDAudioLeadIn() const {
        return dAudioLeadIn;
    }

    void setDAudioLeadIn(double dAudioLeadIn) {
        AstroidInfo::dAudioLeadIn = dAudioLeadIn;
    }

    int getIPreviewTime() const {
        return iPreviewTime;
    }

    void setIPreviewTime(int iPreviewTime) {
        AstroidInfo::iPreviewTime = iPreviewTime;
    }

    const string &getSBackground() const {
        return sBackground;
    }

    void setSBackground(const string &sBackground) {
        AstroidInfo::sBackground = sBackground;
    }
};


#endif //ASTROID_ASTROIDINFO_H
