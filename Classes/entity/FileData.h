//
// Created by qq454 on 2022/03/15.
//

#ifndef ASTROID_FILEDATA_H
#define ASTROID_FILEDATA_H


#include <string>

class FileData{
private:
    /**
     * @details 一个遍历获得的osu文件的路径
     */
     std::string sPath;
    /**
     * @details 背景图片路径，相对于文件的
     */
    std::string sBackGroundPath;
    /**
     * @details 声音档案路径，相对于文件的
     */
    std::string sAudioFilePath;
    /**
     * @details 一个搜索的主键，本地歌曲id号
     */
     int iID=0;
public:
    const std::string &getSPath() const {
        return sPath;
    }

    void setSPath(const std::string &sPath) {
        FileData::sPath = sPath;
    }

    const std::string &getSBackGroundPath() const {
        return sBackGroundPath;
    }

    void setSBackGroundPath(const std::string &sBackGroundPath) {
        FileData::sBackGroundPath = sBackGroundPath;
    }

    const std::string &getSAudioFilePath() const {
        return sAudioFilePath;
    }

    void setSAudioFilePath(const std::string &sAudioFilePath) {
        FileData::sAudioFilePath = sAudioFilePath;
    }

    int getIid() const {
        return iID;
    }

    void setIid(int iId) {
        iID = iId;
    }
};


#endif //ASTROID_IDATA_H
