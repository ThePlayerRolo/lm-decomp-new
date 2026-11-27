#ifndef GAMEMODE_UTIL_H_
#define GAMEMODE_UTIL_H_

#include "Koga/MissionMode.hpp"
#include "Koga/ToolData.hpp"

class JKRArchive;
class MessageReceiver;

namespace Koga {
    class ToolData;

    namespace GameModeUtil {
        void curGameModeCreate();
        void fn_800B9D40();
        void fn_800B9D70();
        void curGameModeDraw();
        void curGameModeDestroy();
        void fn_800B9E0C();
        void fn_800B9E34();
        void fn_800B9E5C();
        void toggleBlackoutTables(MissionMode::Mission mission);
        void fn_800B9EBC();
        void fn_800B9ED0();
        ToolData::JMapData* getPathResource(const char* pName);
        void addJmpReceiver(MessageReceiver* pReceiver);
        JKRArchive* getMapArchive();
        ToolData* getJmpResource(const char* pName);
    };
}

#endif
