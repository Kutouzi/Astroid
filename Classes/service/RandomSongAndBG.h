//
// Created by qq454 on 2022/03/18.
//

#ifndef ASTROID_RANDOMSONGANDBG_H
#define ASTROID_RANDOMSONGANDBG_H

#include <random>
#include "dao/ISql.h"
#include "dao/impl/FileDataSqlImpl.h"

class RandomSongAndBG {
public:
    void DoRandomSongAndBG(FileData *&fileData){
        FileDataSqlImpl *iSql = FileDataSqlImpl::getInstance();
        sqlite3 *sql = nullptr;
        iSql->InitDataBase(sql);
        std::string sTable = "t_file_data";
        int max = iSql->GetDataAmount(sql,sTable);
        uniform_int_distribution<unsigned> u(1,max);
        default_random_engine e(time(nullptr));
        iSql->FindData(sql,u(e),fileData);
        iSql->CloseDataBase(sql);
    }
};


#endif //ASTROID_RANDOMSONGANDBG_H
