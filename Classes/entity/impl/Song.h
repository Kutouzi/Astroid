//
// Created by qq454 on 2022/02/27.
//

#ifndef ASTROID_SONG_H
#define ASTROID_SONG_H


#include <string>

using namespace std;
/**
 * @details 歌曲元信息
 */
class Song{
private:
    /**
     * @details 歌曲英文标题
     */
    string sEnTitle;
    /**
     * @details 歌曲原标题
     */
    wstring sOrgTitle;
    /**
     * @details 歌曲艺术家英文名
     */
    string sEnArtist;
    /**
     * @details 歌曲艺术家原名
     */
    wstring sOrgArtist;
    /**
     * @details 谱面作者
     */
    string  sCreator;
    /**
     * @details 目录下声音档案名称
     */
    string sAudioFilename;

public:

    const string &getSEnTitle() const {
        return sEnTitle;
    }

    void setSEnTitle(const string &sEnTitle) {
        Song::sEnTitle = sEnTitle;
    }

    const wstring &getSOrgTitle() const {
        return sOrgTitle;
    }

    void setSOrgTitle(const wstring &sOrgTitle) {
        Song::sOrgTitle = sOrgTitle;
    }

    const string &getSEnArtist() const {
        return sEnArtist;
    }

    void setSEnArtist(const string &sEnArtist) {
        Song::sEnArtist = sEnArtist;
    }

    const wstring &getSOrgArtist() const {
        return sOrgArtist;
    }

    void setSOrgArtist(const wstring &sOrgArtist) {
        Song::sOrgArtist = sOrgArtist;
    }

    const string &getSCreator() const {
        return sCreator;
    }

    void setSCreator(const string &sCreator) {
        Song::sCreator = sCreator;
    }

    const string &getSAudioFilename() const {
        return sAudioFilename;
    }

    void setSAudioFilename(const string &sAudioFilename) {
        Song::sAudioFilename = sAudioFilename;
    }

};


#endif //ASTROID_SONG_H
