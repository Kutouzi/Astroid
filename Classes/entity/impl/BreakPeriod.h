//
// Created by qq454 on 2022/03/08.
//

#ifndef ASTROID_BREAKPERIOD_H
#define ASTROID_BREAKPERIOD_H

/**
 * @details 歌曲中的空白时间段用作休息
 */
class BreakPeriod {
private:
    /**
     * @details 最小休息时间
     */
    const double MIN_BREAK_DURATION = 650;
    /**
     * @details 休息开始时间
     */
    double dStartTime;
    /**
     * @details 休息结束时间
     */
    double dEndTime;
    /**
     * @details 开始和结束的时间差
     */
    double Duration = dEndTime - dStartTime;
public:

    double getDStartTime() const {
        return dStartTime;
    }

    void setDStartTime(double dStartTime) {
        BreakPeriod::dStartTime = dStartTime;
    }

    double getDEndTime() const {
        return dEndTime;
    }

    void setDEndTime(double dEndTime) {
        BreakPeriod::dEndTime = dEndTime;
    }

    double getDuration() const {
        return Duration;
    }

    void setDuration(double duration) {
        Duration = duration;
    }
};


#endif //ASTROID_BREAKPERIOD_H
