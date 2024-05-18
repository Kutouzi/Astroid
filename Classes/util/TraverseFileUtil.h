//
// Created by qq454 on 2022/03/15.
//

#ifndef ASTROID_TRAVERSEFILEUTIL_H
#define ASTROID_TRAVERSEFILEUTIL_H

#include <string>
#include <vector>
#include "lib/ghc/filesystem.hpp"

using namespace std;

class TraverseFileUtil {
public:
    static TraverseFileUtil *getInstance() {
        return new TraverseFileUtil();
    }
    /**
     * @details 获取目录下所有的文件夹名字
     * @param sRootPath 路径默认为Resources/songs
     * @param fileLists 传入一个string类的list
     */
    void GetAllName(string& sRootPath, vector<string>& fileLists){
        vector<string> pathList;
        for(const auto& it:ghc::filesystem::directory_iterator(sRootPath.c_str())){
            if(it.is_directory()){
                pathList.emplace_back(it.path().string());
            }
        }
        for(const auto& it:pathList){
            for(const auto& o :ghc::filesystem::directory_iterator(it.c_str())){
                if(o.path().string().find(".osu") != string::npos){
                    fileLists.emplace_back(o.path().string());
                }
            }
        }
    }
    /**
     * @details 获取所有osu文件路径
     * @param sRootPath 路径默认为Resources/songs
     * @param fileLists 一个string文件列表
     */
    vector<string> GetAllOsuFile(string& sRootPath){
        vector<string> fileLists;
        GetAllName(sRootPath, fileLists);
#ifdef WIN32
        vector<string> s;
        for (auto it :fileLists) {
            string temp;
            for(int i = 0; i < it.size(); i++){
                if(it.at(i) == '\\'){
                    temp = it.replace(i, 1, 1, '/');
                }
            }
            s.emplace_back(temp);
        }
        return s;
#else
        return fileLists;
#endif
    }

private:
    TraverseFileUtil()=default;
};


#endif //ASTROID_TRAVERSEFILEUTIL_H
