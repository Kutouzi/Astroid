//
// Created by qq454 on 2022/03/25.
//

#ifndef ASTROID_GETLISTDATA_H
#define ASTROID_GETLISTDATA_H


#include "entity/Beatmap.h"
#include "dao/impl/FileDataSqlImpl.h"

class GetListData {
public:
    static vector<Beatmap*> DoGetListData(vector<Beatmap*> &beatmapList){
        sqlite3 *sql = nullptr;
        vector<FileData> fileDataList;
        FileDataSqlImpl *iSql = FileDataSqlImpl::getInstance();
        iSql->InitDataBase(sql);
        iSql->FindAllData(sql,fileDataList);
        for(const auto& it : fileDataList){
            auto *b = new Beatmap;
            string s = it.getSPath();
            OSUFileReadUtil::getInstance()->setAttributes(b,s);
            beatmapList.emplace_back(b);
        }
        return beatmapList;
    }
};


#endif //ASTROID_GETLISTDATA_H
