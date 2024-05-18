//
// Created by qq454 on 2022/03/12.
//

#ifndef ASTROID_TIMINGCONTROLPOINT_H
#define ASTROID_TIMINGCONTROLPOINT_H

/**
 * @details 时间点
 */
class TimingControlPoint {
private:
    /**
     * @details 在声音从音频文件开始以ms为单位的时间
     */
    int iTime =0;
    /**
     * @details 默认的拍持续时间
     */
    const double DEFAULT_BEAT_LENGTH = 1000;
    /**
     * @details 一个拍子的持续时间,如果bUninherited为继承点的话表示滑条速率
     */
    double dBeatLength = DEFAULT_BEAT_LENGTH;
    /**
     * @details 一拍中小节数
     */
    int iMeter = 0;
    /**
     * @details 设置是否是继承时间点，true为非继承，false为继承
     */
    bool bUninherited= true;
public:
    /**
     * @details 计算得出每分钟节拍数，默认是bpm=60
     */
    double dBPM = 60000 / dBeatLength;

    int getITime() const {
        return iTime;
    }

    void setITime(int iTime) {
        TimingControlPoint::iTime = iTime;
    }

    double getDBeatLength() const {
        return dBeatLength;
    }

    void setDBeatLength(double dBeatLength) {
        TimingControlPoint::dBeatLength = dBeatLength;
    }

    int getIMeter() const {
        return iMeter;
    }

    void setIMeter(int iMeter) {
        TimingControlPoint::iMeter = iMeter;
    }

    bool isBUninherited() const {
        return bUninherited;
    }

    void setBUninherited(bool bUninherited) {
        TimingControlPoint::bUninherited = bUninherited;
    }


};


#endif //ASTROID_TIMINGCONTROLPOINT_H
