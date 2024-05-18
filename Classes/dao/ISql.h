//
// Created by qq454 on 2022/02/27.
//

#ifndef ASTROID_ISQL_H
#define ASTROID_ISQL_H

#include <string>
#include "entity/FileData.h"
#include "sqlite3.h"


class ISql{
public:
    virtual bool InitDataBase(sqlite3 *&sql)=0;
    virtual bool CreateTable(sqlite3 *&sql)=0;
    virtual bool DeleteData(sqlite3 *&sql, std::string sKey)=0;
    /**
     * @details 关闭数据库连接
     * @param sql 数据库指针
     * @return 关闭失败为false，否则true
     */
    virtual bool CloseDataBase(sqlite3 *&sql){
        if(sqlite3_close(sql)){
            return true;
        }
        return false;
    };
    virtual int GetDataAmount(sqlite3 *&sql,std::string &sTable){
        sqlite3_stmt *pStmt = nullptr;
        std::string s ="SELECT * FROM "+ sTable +";";
        const char *zSql=s.c_str();
        int index = 0;
        if(sqlite3_prepare_v2(sql,zSql,strlen(zSql),&pStmt, nullptr) == SQLITE_OK ){
            while (true){
                int r = sqlite3_step(pStmt);
                if (r == SQLITE_DONE){
                    break;
                }
                else if (r == SQLITE_ROW){
                    index++;
                }
            }
            return index;
        }
        return index;
    }
};
#endif //ASTROID_ISQL_H
