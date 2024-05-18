//
// Created by qq454 on 2022/03/07.
//

#ifndef ASTROID_OSUHITOBJECTS_H
#define ASTROID_OSUHITOBJECTS_H


#include "enums/OsuObjectEnums.h"

/**
 * @details osu的打击物件位置、时间和各种信息
 */
class OsuHitObjects{
private:
    /**
     * @details 相对窗口位置,开始和结束的x和y，如果hitcircle类型开始和结束值相同
     */
    int x=0;
    int y=0;
    int ex=0;
    int ey=0;
    /**
     * @details 往返共计次数
     */
     int count = 0;
    /**
     * @details 估算长度
     */
    double length=0;
    /**
     * @details 时间位置
     */
    int offset=0;
    int endoffset=0;
    /**
     * @details 物件类型
     */
    OsuObjectEnums eObjectType = OsuObjectEnums::HitCircle;
public:
    int getCount() const {
        return count;
    }

    void setCount(int count) {
        OsuHitObjects::count = count;
    }

    int getEndoffset() const {
        return endoffset;
    }

    void setEndoffset(int endoffset) {
        OsuHitObjects::endoffset = endoffset;
    }

    double getLength() const {
        return length;
    }

    void setLength(double length) {
        OsuHitObjects::length = length;
    }

    int getEx() const {
        return ex;
    }

    void setEx(int ex) {
        OsuHitObjects::ex = ex;
    }

    int getEy() const {
        return ey;
    }

    void setEy(int ey) {
        OsuHitObjects::ey = ey;
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        OsuHitObjects::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        OsuHitObjects::y = y;
    }

    int getOffset() const {
        return offset;
    }

    void setOffset(int offset) {
        OsuHitObjects::offset = offset;
    }

    OsuObjectEnums getEObjectType() const {
        return eObjectType;
    }

    void setEObjectType(OsuObjectEnums eObjectType) {
        OsuHitObjects::eObjectType = eObjectType;
    }
};


#endif //ASTROID_OSUHITOBJECTS_H
