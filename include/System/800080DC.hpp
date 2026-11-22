#ifndef _800080DC_HPP
#define _800080DC_HPP

#include <types.h>

enum Enum800080DCState {
    STATE_80DC_DEFAULT = 0,
    STATE_80DC_1 = 1,
    STATE_80DC_2 = 2,
    STATE_80DC_3 = 3,
    STATE_80DC_4 = 4,
    STATE_80DC_8 = 8,
};

class Struct800080DCOne {
    public:
        inline Struct800080DCOne() { 
            mState = STATE_80DC_DEFAULT;
            _4 = 1; 
        }
        
        void fn_800080DC();
        void fn_8000812C();
        void fn_800081A8();

        inline u32 getState() { return mState; }
        inline void setState(u32 state) { mState = state; }
        inline void setUnk4(u32 val) { _4 = val; }
        inline void setUnk8(u32 val) { _8 = val; }
    private:
        u32 mState;
        u32 _4;
        u32 _8;
};

// Unsure of return types/args
void fn_80008394();
void fn_800083A4(u32);
void fn_800083B4(u32);

extern Struct800080DCOne lbl_803A3810;

#endif
