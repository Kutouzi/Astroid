//
// Created by qq454 on 2022/03/08.
//

#ifndef ASTROID_BEATMAP_H
#define ASTROID_BEATMAP_H

#include <vector>
#include "entity/impl/BeatmapInfo.h"
#include "entity/impl/BreakPeriod.h"
#include "entity/impl/TimingControlPoint.h"

/**
 * @details 整合休息列表，物件信息，歌曲信息和谱面信息作为谱面对象
 */
class Beatmap {
public:
    /**
     * @details 创建歌曲信息
     */
    Song *song = new Song();
    /**
     * @details 谱面信息包括当前谱面信息和歌曲元信息
     */
    BeatmapInfo *beatmapInfo = new BeatmapInfo(song);
    /**
     * @details 谱面休息列表
     */
    std::vector<BreakPeriod> *breakPeriod;
    /**
     * @details 时间点信息列表
     */
    std::vector<TimingControlPoint*> timeControlPoint{};
    /**
     * @details 谱面物件列表
     */
    std::vector<OsuHitObjects*> osuHitObjects{};
    /**
     * @details 释放类内对象
     */
    ~Beatmap(){
        delete beatmapInfo;
        delete song;
    }
};


#endif //ASTROID_BEATMAP_H
