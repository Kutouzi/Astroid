//
// Created by qq454 on 2022/03/23.
//

#ifndef ASTROID_INITBEATMAP_H
#define ASTROID_INITBEATMAP_H

#include "entity/Beatmap.h"
#include "util/OSUFileReadUtil.h"
#include <codecvt>

class InitBeatmap{
public:
    Beatmap * DoInitBeatmap(std::string sPath){
        auto *beatmap = new Beatmap();
        OSUFileReadUtil::getInstance()->setAttributes(beatmap,sPath);
        wstring s = beatmap->song->getSOrgArtist();
        return beatmap;
    }
};

#endif //ASTROID_INITBEATMAP_H
