//
// Created by qq454 on 2022/03/18.
//

#ifndef ASTROID_ASTROIDOBJECT_H
#define ASTROID_ASTROIDOBJECT_H


#include "enums/AstroidObjectEnums.h"

class AstroidObject {
    /**
     * @details 相对窗口位置
     */
    int x=0;
    int y=0;
    int ex=0;
    int ey=0;
    /**
     * @details 一个高度
     */
    double height=0;
    /**
     * @details 到下一个的距离
     */
     int distance=-1;
    /**
     * @details 时间位置
     */
    int offset=0;
    /**
     * @details 物件类型
     */
    AstroidObjectEnums eObjectType = AstroidObjectEnums::TwinkleStar;
public:
    int getDistance() const {
        return distance;
    }

    void setDistance(int distance) {
        AstroidObject::distance = distance;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double height) {
        AstroidObject::height = height;
    }

    int getX() const {
        return x;
    }

    void setX(int x) {
        AstroidObject::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        AstroidObject::y = y;
    }

    int getOffset() const {
        return offset;
    }

    void setOffset(int offset) {
        AstroidObject::offset = offset;
    }

    int getEx() const {
        return ex;
    }

    void setEx(int ex) {
        AstroidObject::ex = ex;
    }

    int getEy() const {
        return ey;
    }

    void setEy(int ey) {
        AstroidObject::ey = ey;
    }

    AstroidObjectEnums getEObjectType() const {
        return eObjectType;
    }

    void setEObjectType(AstroidObjectEnums eObjectType) {
        AstroidObject::eObjectType = eObjectType;
    }
};


#endif //ASTROID_ASTROIDOBJECT_H
