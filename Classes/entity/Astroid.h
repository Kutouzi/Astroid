//
// Created by qq454 on 2022/03/18.
//

#ifndef ASTROID_ASTROID_H
#define ASTROID_ASTROID_H


#include <vector>
#include "entity/impl/Song.h"
#include "entity/impl/AstroidInfo.h"
#include "entity/impl/BreakPeriod.h"
#include "entity/impl/TimingControlPoint.h"
#include "entity/impl/AstroidObject.h"

class Astroid {
public:
    /**
     * @details 创建歌曲信息
     */
    Song *song = new Song();
    /**
     * @details 谱面信息包括当前谱面信息和歌曲元信息
     */
     AstroidInfo *astroidInfo = new AstroidInfo(song);
    /**
     * @details 谱面休息列表
     */
    std::vector<BreakPeriod> *breakPeriod;
    /**
     * @details 时间点信息列表
     */
    std::vector<TimingControlPoint*> timeControlPoint{};
    /**
     * @details 游戏物件
     */
     std::vector<AstroidObject*> astroidObject{};
     /**
      * @details 释放对象
      */
    ~Astroid(){
        delete song;
        delete astroidInfo;
    }
};


#endif //ASTROID_ASTROID_H
