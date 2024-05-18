//
// Created by qq454 on 2022/03/22.
//

#ifndef ASTROID_RWCACHE_H
#define ASTROID_RWCACHE_H

#include <string>
#include <fstream>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "entity/FileData.h"

USING_NS_CC;

class RWCache {
private:
#ifdef WIN32
    const std::string sFilePathCache = FileUtils::getInstance()->getSearchPaths().at(0) + "/cache/PathCache.json";
    const std::string sScoreCache = FileUtils::getInstance()->getSearchPaths().at(0) + "/cache/ScoreCache.json";
#else
    const std::string sFilePathCache = FileUtils::getInstance()->getSearchPaths().at(0) + "/storage/emulated/0/Download/Resources/cache/PathCache.json";
    const std::string sScoreCache = FileUtils::getInstance()->getSearchPaths().at(0) + "/storage/emulated/0/Download/Resources/cache/ScoreCache.json";
#endif
    RWCache()=default;
    std::string ReadFile(const std::string& filename){
        FILE *f = fopen(filename.c_str(), "rb");
        char *buffer = new char[1024];
        unsigned int n = fread(buffer, 1, 1024, f);
        fclose(f);
        std::string result;
        if(n>=0){
            result.append(buffer, 0, n);
        }
        delete []buffer;
        return result;
    }
public:
    static RWCache *getInstance() {
        return new RWCache();
    }
    void InitFile(const std::string& fs){
        std::ofstream file;
        file.open(fs);
        file.close();
    }
    bool ReadPathCache(FileData *&fileData) {
        rapidjson::Document doc;
        std::string jsonstr = ReadFile(sFilePathCache);
        doc.Parse<rapidjson::kParseDefaultFlags>(jsonstr.c_str());
        if (doc.HasParseError()) {
            return false;
        }
        if (doc.HasMember("sPath")) {
            rapidjson::Value &s = doc["sPath"];
            fileData->setSPath(s.GetString());
        }
        if (doc.HasMember("sBackGroundPath")) {
            rapidjson::Value &s = doc["sBackGroundPath"];
            fileData->setSBackGroundPath(s.GetString());
        }
        if (doc.HasMember("sAudioFilePath")) {
            rapidjson::Value &s = doc["sAudioFilePath"];
            fileData->setSAudioFilePath(s.GetString());
        }
        return true;
    }
    double ReadScoreCache() {
        rapidjson::Document doc;
        std::string jsonstr = ReadFile(sScoreCache);
        doc.Parse<rapidjson::kParseDefaultFlags>(jsonstr.c_str());
        if (doc.HasParseError()) {
            return false;
        }
        if (doc.HasMember("Score")) {
            rapidjson::Value &s = doc["Score"];
            return s.GetDouble();
        }
        return -1;
    }
    bool WritePathCache(FileData *&fileData){
        InitFile(sFilePathCache);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType &allocator=doc.GetAllocator();
        std::string jsonstr = ReadFile(sFilePathCache);
        doc.Parse<rapidjson::kParseDefaultFlags>(jsonstr.c_str());
        rapidjson::Value value;
        rapidjson::StringBuffer buffer;
        doc.AddMember("sPath", value.SetString(fileData->getSPath().c_str(),fileData->getSPath().length()), doc.GetAllocator());
        doc.AddMember("sBackGroundPath", value.SetString(fileData->getSBackGroundPath().c_str(),fileData->getSBackGroundPath().length()), doc.GetAllocator());
        doc.AddMember("sAudioFilePath", value.SetString(fileData->getSAudioFilePath().c_str(),fileData->getSAudioFilePath().length()), doc.GetAllocator());
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Parse<rapidjson::kParseDefaultFlags>(sFilePathCache.c_str());
        doc.Accept(writer);
        std::ofstream outfile(sFilePathCache, std::ios::trunc);
        if(outfile){
            outfile << buffer.GetString();
            outfile.close();
            return true;
        }
        return false;
    }
    bool WriteScoreCache(double score){
        InitFile(sScoreCache);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType &allocator=doc.GetAllocator();
        std::string jsonstr = ReadFile(sScoreCache);
        doc.Parse<rapidjson::kParseDefaultFlags>(jsonstr.c_str());
        rapidjson::Value value;
        rapidjson::StringBuffer buffer;
        doc.AddMember("Score", value.SetDouble(score), doc.GetAllocator());
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Parse<rapidjson::kParseDefaultFlags>(sScoreCache.c_str());
        doc.Accept(writer);
        std::ofstream outfile(sScoreCache, std::ios::trunc);
        if(outfile){
            outfile << buffer.GetString();
            outfile.close();
            return true;
        }
        return false;
    }
};


#endif //ASTROID_RWCACHE_H
