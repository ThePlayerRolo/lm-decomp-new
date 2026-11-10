#ifndef ACTORLIST_HPP
#define ACTORLIST_HPP

#include <types.h>
#include <JSystem/JUtility/JUTColor.hpp>


class ActorData {
    public:
        /* 0x0 */ u32 mGroupID;
        /* 0x4 */ u16 _4;
        /* 0x6 */ u16 _6; // Un-used?
        /* 0x8 */ u16 mFlags; // TODO make a bitflag struct/enum maybe?
        /* 0xC */ u32 _C; // Could be void* based on functions that call getActorData, but would need to confirm
        /* 0x10 */ u32 _10; // Could be void* based on functions that call getActorData, but would need to confirm
        /* 0x14 */ s16 _14;
        /* 0x18 */ const char* mActorName;
 
        // This might make more sense in a Util class, unsure at this time without digging more.
        static u32 getGroupID(s32);
        static u16 fn_8006A36C(s32);
        static u32 getEnemyBrightColor(s32);
        static const char* getActorName(s32);
        static u16 checkFlags(s32, s32);
        static ActorData* getActorData(s32);
    
    private:
        static ActorData sActorData[];
};

#endif
