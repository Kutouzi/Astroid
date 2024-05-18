//
// Created by qq454 on 2022/03/16.
//

#ifndef ASTROID_FORMATFILEDATA_H
#define ASTROID_FORMATFILEDATA_H

USING_NS_CC;

#include "util/TraverseFileUtil.h"
#include "entity/FileData.h"
#include "util/OSUFileReadUtil.h"
#include "dao/impl/FileDataSqlImpl.h"
#include "lib/ghc/filesystem.hpp"

class FormatFileData {
public:
    void DoFormatFileData(){
        TraverseFileUtil *traverseFileUtil = TraverseFileUtil::getInstance();
        OSUFileReadUtil *osuFileReadUtil = OSUFileReadUtil::getInstance();
        FileDataSqlImpl *iSql = FileDataSqlImpl::getInstance();
        sqlite3 *sql = nullptr;
        iSql->InitDataBase(sql);
        iSql->CreateTable(sql);
        auto *beatmap = new Beatmap();
        vector<string> fileList;

#ifdef WIN32
        string sRootPath=FileUtils::getInstance()->fullPathForFilename("index.txt");
        sRootPath=sRootPath.substr(0,sRootPath.find_last_of('/'))+"/songs";
#else
        string sRootPath="/storage/emulated/0/Download/Resources/songs";
#endif
        fileList = traverseFileUtil->GetAllOsuFile(sRootPath);
        auto *fileData = new FileData();
        int IidCount = 1;
        for (auto it = fileList.begin(); it != fileList.end(); it++,IidCount++){
            fileData->setIid(IidCount);
            fileData->setSPath(*it);
            osuFileReadUtil->setAttributes(beatmap,*it);
            fileData->setSAudioFilePath(beatmap->song->getSAudioFilename());
            fileData->setSBackGroundPath(beatmap->beatmapInfo->getSBackground());
            iSql->InsertData(sql,fileData);
        }
        iSql->CloseDataBase(sql);
        delete fileData;
        delete beatmap;
   }

};


#endif //ASTROID_FORMATFILEDATA_H
