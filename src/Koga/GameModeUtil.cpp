#include "Koga/GameModeUtil.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/EnemyGenManager.hpp"
#include "Koga/GameMode.hpp"
#include "Koga/JmpMessage.hpp"
#include "Koga/MissionMode.hpp"
#include "Koga/Message.hpp"

namespace Koga { 
    namespace GameModeUtil {
        
        void curGameModeCreate() {
            GameModeBase::sCurrentGameMode = MissionMode::create();
        }

        void curGameModeLoadEnemyInfo() {
            GameModeBase::sCurrentGameMode->loadEnemyInfo();
        }

        void fn_800B9D70() {
            GameModeBase::sCurrentGameMode->vt_14();
        }

        void curGameModeDraw() {
            GameModeBase::sCurrentGameMode->draw();
        }

        void curGameModeDestroy() {
            delete GameModeBase::sCurrentGameMode;
        }

        void fn_800B9E0C() {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->getEnManager()->fn_800E46C0();
        }

        void fn_800B9E34() {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->getJmpMsgSender()->fn_800EAB1C();
        }

        void fn_800B9E5C() {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->getJmpMsgSender()->vt_10();
        }

        void toggleBlackoutTables(MissionMode::Mission mission) {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->toggleBlackoutTables(mission);
        }

        void fn_800B9EBC() {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->getEnemyGenManager()->setUnk8(false);
        }

        void fn_800B9ED0() {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->getEnemyGenManager()->setUnk8(true);
        }

        ToolData::JMapData* getPathResource(const char* pName) {
            MissionMode* missionMode = MissionMode::getMissionMode();

            return reinterpret_cast<ToolData::JMapData*>(missionMode->getMapArchiveResource(pName, 'PATH'));
        }

        void addJmpReceiver(MessageReceiver* pReceiver) {
            MissionMode* missionMode = MissionMode::getMissionMode();

            missionMode->addJmpReceiver(pReceiver);
        }

        JKRArchive* getMapArchive() {
            return MissionMode::getMissionMode()->getMapArchive();
        }

        ToolData* getJmpResource(const char* pName) {
            MissionMode* missionMode = MissionMode::getMissionMode();

            return missionMode->getJmpResource(pName);
        }
    }
}
