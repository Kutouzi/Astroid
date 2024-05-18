//
// Created by qq454 on 2022/03/08.
//

#ifndef ASTROID_BEATMAPINFO_H
#define ASTROID_BEATMAPINFO_H


#include "Song.h"
#include "OsuHitObjects.h"
/**
 * @details 铺面信息在此处，并且创建歌曲元信息
 */
class BeatmapInfo {
private:
    /**
     * @details 公开的歌曲编号
     */
    int iBeatmapID = 0;
    /**
     * @details 歌曲集合编号
     */
    int iBeatmapSetID = 0;
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
      * @details 基础速度乘速
      */
      double fMultiplier = 0.0;
    /**
     * @details 目录下歌曲背景图片名称
     */
    string sBackground;
public:
    explicit BeatmapInfo(Song *song){
        this->song=song;
    }
    Song *getSong() const {
        return song;
    }

    double getFMultiplier() const {
        return fMultiplier;
    }

    void setFMultiplier(double fMultiplier) {
        BeatmapInfo::fMultiplier = fMultiplier;
    }

    int getIBeatmapId() const {
        return iBeatmapID;
    }

    void setIBeatmapId(int iBeatmapId) {
        iBeatmapID = iBeatmapId;
    }

    int getIBeatmapSetId() const {
        return iBeatmapSetID;
    }

    void setIBeatmapSetId(int iBeatmapSetId) {
        iBeatmapSetID = iBeatmapSetId;
    }


    void setSong(Song *song) {
        BeatmapInfo::song = song;
    }

    const string &getSDifficulty() const {
        return sDifficulty;
    }

    void setSDifficulty(const string &sDifficulty) {
        BeatmapInfo::sDifficulty = sDifficulty;
    }

    const string &getSPath() const {
        return sPath;
    }

    void setSPath(const string &sPath) {
        BeatmapInfo::sPath = sPath;
    }

    double getDAudioLeadIn() const {
        return dAudioLeadIn;
    }

    void setDAudioLeadIn(double dAudioLeadIn) {
        BeatmapInfo::dAudioLeadIn = dAudioLeadIn;
    }

    int getIPreviewTime() const {
        return iPreviewTime;
    }

    void setIPreviewTime(int iPreviewTime) {
        BeatmapInfo::iPreviewTime = iPreviewTime;
    }

    const string &getSBackground() const {
        return sBackground;
    }

    void setSBackground(const string &sBackground) {
        BeatmapInfo::sBackground = sBackground;
    }
};


#endif //ASTROID_BEATMAPINFO_H
