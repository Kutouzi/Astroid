//
// Created by qq454 on 2022/02/23.
//

#ifndef ASTROID_FILEDATASQLIMPL_H
#define ASTROID_FILEDATASQLIMPL_H

#include "sqlite3.h"
#include "dao/ISql.h"
#include "entity/impl/Song.h"
#include "util/OSUFileReadUtil.h"
#include <string>
#include <iostream>

USING_NS_CC;
/**
 * @details 用于在列表显示歌曲和谱面名字和信息，但不去创建歌曲和谱面对象
 */
class FileDataSqlImpl : public ISql {
public:
    static FileDataSqlImpl *getInstance() {
        return new FileDataSqlImpl();
    }

    /**
     * 用于初始化创建文件路径数据库
     * @param sql 传入一个用于操作数据库的指针
     * @return 创建成功返回true且传入参数*sql被赋值，否则false且传入参数*sql为null
     */
    bool InitDataBase(sqlite3 *&sql) override {
#ifdef WIN32
        std::string sDataBasePath = FileUtils::getInstance()->getSearchPaths().at(0) + "/data/FileData.db";
#else
        std::string sDataBasePath = "/storage/emulated/0/Download/Resources/data/FileData.db";
#endif
        try {
            int result = sqlite3_open(sDataBasePath.c_str(), &sql);
            if (result == SQLITE_OK) {
                std::cout << "FileData database created and connected successfully" << std::endl;
                return true;
            } else {
                std::cout << "FileData database connected failed" << std::endl;
                return false;
            }
        } catch (std::bad_exception &e) {
            std::cout << "Cant create FileData database" << std::endl;
            sql = nullptr;
            return false;
        }
    }

    /**
     * @details 创建文件路径表
     * @param sql 数据库指针
     * @return 创建成功返回true，否则为false
     */
    bool CreateTable(sqlite3 *&sql) override {
        const char *zSql = "CREATE TABLE IF NOT EXISTS t_file_data (iID integer PRIMARY KEY, sBackGroundPath text NOT NULL, sAudioFilePath text NOT NULL, sPath text NOT NULL);";
        sqlite3_stmt *pStmt = nullptr;
        if (sqlite3_prepare_v2(sql, zSql, strlen(zSql), &pStmt, nullptr) == SQLITE_OK) {
            if (sqlite3_step(pStmt) == SQLITE_OK) {
                return true;
            }
            return false;
        }
        return false;
    }

    /**
     *
     * @param sql 数据库指针
     * @param fileData 文件路径对象
     * @return 创建成功返回true，否则为false
     */
    bool InsertData(sqlite3 *&sql, FileData *&fileData) {
        const char *zSql = "REPLACE INTO t_file_data VALUES(@iID,@sBackGroundPath,@sAudioFilePath,@sPath);";
        sqlite3_stmt *pStmt = nullptr;
        sqlite3_prepare_v2(sql, zSql, strlen(zSql), &pStmt, nullptr);
        sqlite3_bind_int(pStmt, sqlite3_bind_parameter_index(pStmt, "@iID"), fileData->getIid());
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, "@sBackGroundPath"),
                          fileData->getSBackGroundPath().c_str(), fileData->getSBackGroundPath().length(), nullptr);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, "@sAudioFilePath"),
                          fileData->getSAudioFilePath().c_str(), fileData->getSAudioFilePath().length(), nullptr);
        sqlite3_bind_text(pStmt, sqlite3_bind_parameter_index(pStmt, "@sPath"),
                          fileData->getSPath().c_str(), fileData->getSPath().length(), nullptr);
        int r = sqlite3_step(pStmt);
        sqlite3_reset(pStmt);
        return r;
    }

    bool DeleteData(sqlite3 *&sql, std::string sKey) override {
        return false;
    }

    /**
     * @details 查找指定key的对象
     * @param sql 一个sql指针
     * @param sKey 为无符号整形
     * @param fileData 传入对象以让此函数赋值
     * @return 执行成功不管是否查找到数据都为true，执行失败为false
     */
    bool FindData(sqlite3 *&sql, unsigned int sKey, FileData *&fileData) {
        fileData->setIid(sKey);
        const char *zSql = "SELECT * FROM t_file_data WHERE iID = @iID;";
        sqlite3_stmt *pStmt = nullptr;
        sqlite3_prepare_v2(sql, zSql, strlen(zSql), &pStmt, nullptr);
        sqlite3_bind_int(pStmt, sqlite3_bind_parameter_index(pStmt, "@iID"), fileData->getIid());
        while (true) {
            static int flag = 1;
            int i;
            int r = sqlite3_step(pStmt);
            if (r == SQLITE_DONE) {
                cout << "exec finish" << endl;
                break;
            } else if (r == SQLITE_ROW) {
                int cNum = 0;
                cNum = sqlite3_column_count(pStmt);
                if (flag) {
                    for (i = 0; i < cNum; i++) {
                        const char *p = sqlite3_column_name(pStmt, i);
                        string ss = p;
                        if (ss == "sBackGroundPath") {
                            fileData->setSBackGroundPath(reinterpret_cast<const char *const>(sqlite3_column_text(pStmt, i)));
                        } else if (ss == "sAudioFilePath") {
                            fileData->setSAudioFilePath(reinterpret_cast<const char *const>(sqlite3_column_text(pStmt, i)));
                        } else if (ss == "sPath") {
                            fileData->setSPath(reinterpret_cast<const char *const>(sqlite3_column_text(pStmt, i)));
                        }
                    }
                    flag = 0;
                }
            }
        }
        return true;
    }
    vector<FileData> FindAllData(sqlite3 *&sql, vector<FileData> &fileDataList){
        const char *zSql = "SELECT * FROM t_file_data;";
        sqlite3_stmt *pStmt = nullptr;
        sqlite3_prepare_v2(sql, zSql, strlen(zSql), &pStmt, nullptr);
        while (true) {
            int i;
            int r = sqlite3_step(pStmt);
            if (r == SQLITE_DONE) {
                cout << "exec finish" << endl;
                break;
            } else if (r == SQLITE_ROW) {
                int cNum = 0;
                cNum = sqlite3_column_count(pStmt);
                FileData fileData;
                for (i = 0; i < cNum; i++) {
                    const char *p = sqlite3_column_name(pStmt, i);
                    string ss = p;
                    if (ss == "sBackGroundPath") {
                        fileData.setSBackGroundPath(reinterpret_cast<const char *const>(sqlite3_column_text(pStmt, i)));
                    } else if (ss == "sAudioFilePath") {
                        fileData.setSAudioFilePath(reinterpret_cast<const char *const>(sqlite3_column_text(pStmt, i)));
                    } else if (ss == "sPath") {
                        fileData.setSPath(reinterpret_cast<const char *const>(sqlite3_column_text(pStmt, i)));
                    }

                }
                fileDataList.emplace_back(fileData);
            }
        }
        return fileDataList;
    }

private:

    FileDataSqlImpl() = default;

};


#endif //ASTROID_FILEDATASQLIMPL_H
