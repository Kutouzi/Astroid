//
// Created by qq454 on 2022/03/26.
//

#ifndef ASTROID_OSUTOAST_H
#define ASTROID_OSUTOAST_H


#include "util/OSUFileReadUtil.h"
#include "entity/Beatmap.h"
#include "entity/Astroid.h"

class OsuToAst {
private:
    inline int CompDistance(int tempx,int tempy,int nextx,int nexty){
        return std::sqrt(std::pow(tempx-nextx,2)-std::pow(tempy-nexty,2));
    }
public:
    void DoOsuToAst(std::string sPath,Beatmap *&beatmap,Astroid *&astroid){
        auto osuFileReadUtil=OSUFileReadUtil::getInstance();
        osuFileReadUtil->ReadOSUFile(sPath,beatmap);
        astroid->song->setSCreator(beatmap->song->getSCreator());
        astroid->song->setSEnArtist(beatmap->song->getSEnTitle());
        astroid->song->setSOrgTitle(beatmap->song->getSOrgTitle());
        astroid->song->setSEnTitle(beatmap->song->getSEnTitle());
        astroid->song->setSOrgArtist(beatmap->song->getSOrgArtist());
        astroid->song->setSAudioFilename(beatmap->song->getSAudioFilename());
        astroid->astroidInfo->setSBackground(beatmap->beatmapInfo->getSBackground());
        astroid->astroidInfo->setSDifficulty(beatmap->beatmapInfo->getSDifficulty());
        astroid->astroidInfo->setDAudioLeadIn(beatmap->beatmapInfo->getDAudioLeadIn());
        astroid->astroidInfo->setIPreviewTime(beatmap->beatmapInfo->getIPreviewTime());
        astroid->timeControlPoint = beatmap->timeControlPoint;
        double endTime = 0;
        auto *st=new TimingControlPoint();
        auto *rt=new TimingControlPoint();
        bool isFirstChanged = false; //是否改变过
        for(auto t :beatmap->timeControlPoint){
            if(t->isBUninherited()){
                rt=t;
            } else{
                st=t;
                isFirstChanged = true;
            }
            for(auto o : beatmap->osuHitObjects){
                if(o->getEObjectType() == OsuObjectEnums::Slider){
//                    if(o->getOffset() >=rt->getITime() && o->getOffset() < st->getITime() && isHave){
//                        endTime = o->getOffset() + (o->getLength() * o->getCount()) / ((-100 / to->getDBeatLength()) *beatmap->beatmapInfo->getFMultiplier() * 100) * rt->getDBeatLength();
//                        o->setEndoffset(endTime);
//                    }
                    //是否在红线后面,在绿线后面,且不是初始的绿线，是就是用前一个红线和绿线计算
                    if(o->getOffset()>=rt->getITime() && o->getOffset() >= st->getITime() && isFirstChanged){
                        endTime = o->getOffset() + (o->getLength() * o->getCount()) / ((-100 / st->getDBeatLength()) *beatmap->beatmapInfo->getFMultiplier() * 100) * rt->getDBeatLength();
                        o->setEndoffset(endTime);
                    }
                }
            }
        }

        for(auto it : beatmap->osuHitObjects){
            auto *a = new AstroidObject();
            a->setX(it->getX() / 640.0f * 1280.0f);
            a->setY(it->getY() / 480.0f * 720.0f);
            a->setOffset(it->getOffset());
            if(it->getEObjectType() == OsuObjectEnums::HitCircle){
                a->setEObjectType(AstroidObjectEnums::TwinkleStar);
                a->setEx(a->getX());
                a->setEy(a->getY());
            } else if(it->getEObjectType() == OsuObjectEnums::Slider){
                a->setEObjectType(AstroidObjectEnums::StreamStar);
                a->setEx(it->getEx() / 640.0f * 1280.0f);
                a->setEy(it->getEy() / 480.0f * 720.0f);
                a->setHeight(it->getEndoffset() - it->getOffset());
            } else if(it->getEObjectType() == OsuObjectEnums::Spinner){
                a->setEObjectType(AstroidObjectEnums::StreamStar);
                a->setEx(a->getX());
                a->setEy(a->getY());
                a->setHeight(it->getEndoffset() - it->getOffset());
            }
            astroid->astroidObject.emplace_back(a);
        }
        for(int i =0;i<beatmap->osuHitObjects.size()-1;i++){
            if(beatmap->osuHitObjects[i]->getEObjectType() == OsuObjectEnums::HitCircle){
                astroid->astroidObject[i]->setDistance(
                        CompDistance(beatmap->osuHitObjects[i]->getX(),beatmap->osuHitObjects[i]->getY(),
                                     beatmap->osuHitObjects[i+1]->getX(),beatmap->osuHitObjects[i]->getY())*800/1280);
            }else if(beatmap->osuHitObjects[i]->getEObjectType() == OsuObjectEnums::Slider ||
            beatmap->osuHitObjects[i]->getEObjectType() == OsuObjectEnums::Spinner){
                astroid->astroidObject[i]->setDistance(
                        CompDistance(beatmap->osuHitObjects[i]->getEx(),beatmap->osuHitObjects[i]->getEy(),
                                     beatmap->osuHitObjects[i+1]->getX(),beatmap->osuHitObjects[i]->getY())*800/1280);
            }
        }
    }
};


#endif //ASTROID_OSUTOAST_H
