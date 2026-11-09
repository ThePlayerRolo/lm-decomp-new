#ifndef ENEMY_GEN_MANAGER_HPP
#define ENEMY_GEN_MANAGER_HPP

#include <types.h>
#include <JSystem/JORReflexible.hpp>
#include <JSystem/JGeometry/JGVec3.hpp>

#include "MR/Array.hpp"
#include "Koga/EnManager.hpp"
#include "Koga/Message.hpp"
#include "Koga/ToolData.hpp"
#include "Sato/IncludeStrategy.hpp"
#include "Koga/800E634C.hpp"

namespace Koga {
    class EnManager;
}

class EnemyStrategy;
class EnZako;

class EnemyGenerator : public JORReflexible, public IncludeStrategy {
public:
    EnemyGenerator();
    virtual ~EnemyGenerator();

    void fn_800C2500();
    void fn_800C2560();
    EnZako* fn_800C25F0(s32, s32); // Need to validate arg / return type.
    ToolDataRef fn_800C2784();
    Koga::ToolData* fn_800C2798();
    s32 fn_800C2830(const char*);
     // Need to validate arg / return type.
    void fn_800C287C(void*); // dynamic casts to EnZako and Koga::Observer<GeneratorEvent, void>
    EnemyStrategy* getGenStrategy();

    inline void updateStrategy() {
        if (getStrategy() != nullptr) { 
            if (fn_800E7174(&mPos, -1) == false) {
                _860 = 0;
            }

            getStrategy()->update();
        }
    }
    inline bool isSameGenerator(const ToolDataRef& key) {
        ToolDataRef ref = fn_800C2784();
        return ref.isSameEntry(key);
    }

    /* 0x808 */ Koga::ToolData* _808;
    /* 0x80C */ s32 _80C;
    /* 0x810 */ Koga::EnManager* _810;
    /* 0x814 */ s32 _814; // Generator type? See vt_C
    /* 0x818 */ Koga::ToolData mGenPath;
    /* 0x820 */ MR::ArrayHolder<EnZako*, 0xF> _820;
    /* 0x860 */ s32 _860;
    /* 0x864 */ JGeometry::TVec3f mPos;
    /* 0x870 */ u16 _870;
};

#define MAX_ENEMY_GENS 0x14

namespace Koga {
    class EnemyGenManager : public JORReflexible, public MessageReceiver {
    public:
        EnemyGenManager();
        /* 0x08 */ virtual ~EnemyGenManager();
        /* 0x0C */ virtual BOOL vt_0C(ToolDataRef*); // Checks to see if input is a generator, maybe something to do with adding/loading?
        /* 0x10 */ virtual BOOL vt_10(ToolDataRef*); // Maybe something to do with removing / deleting
        /* 0x14 */ virtual BOOL vt_14(ToolDataRef*, char* message);

        void fn_800C2F44();
        void fn_800C2FE8(void*); // Need to validate arg / return type.

        inline void setUnk8(bool val) { _8 = val; }
        inline EnemyGenerator* begin() { return &mEnemyGens[0]; }
        inline EnemyGenerator* last() { return &mEnemyGens[MAX_ENEMY_GENS - 1]; }
        inline EnemyGenerator* end() { return &mEnemyGens[MAX_ENEMY_GENS]; }

        inline EnemyGenerator* searchEnemyGen(Koga::ToolData* pData, s32 entryIdx) {
            ToolDataRef ref;
            ref.setToolData(pData);
            ref.setEntryIndex(entryIdx);

            EnemyGenerator* curr = begin();
            EnemyGenerator* last = end();

            while (curr != last && !curr->isSameGenerator(ref)) {
                curr++;
            }

            return curr;
        }

        inline EnemyGenerator* findFreeEnemyGen() {
            EnemyGenerator* curr = begin();
            EnemyGenerator* last = end();

            while (curr != last && curr->getGenStrategy() != nullptr) {
                curr++;
            }

            return curr;
        }

    private:
        /* 0x4 */  EnemyGenerator* mEnemyGens;
        /* 0x8 */ bool _8;
    };

};

#endif
