#ifndef _800080DC_HPP
#define _800080DC_HPP

#include <dolphin/types.h>

#include "System/Scenes/ScreenTransition.hpp"

#define SCREEN_TRANSITION_IDLE 0
#define SCREEN_TRANSITION_OUT 1
#define SCREEN_TRANSITION_UNUSED_2 2
#define SCREEN_TRANSITION_IN 3
#define SCREEN_TRANSITION_REQUESTED 4
#define SCREEN_TRANSITION_DONE 8

class ScreenTransitionCtrl {
    public:
        inline ScreenTransitionCtrl() { 
            mState = SCREEN_TRANSITION_IDLE;
            mType = SCREEN_TRANSITION_FADE; 
        }
        
        void startTransitionIn();
        void update();
        void draw();

        static void requestTransition();
        static void setTransitionType(ScreenTransitionType);
        static void setTransitionLength(s32);

        inline u32 getState() { return mState; }
        inline void setState(u32 state) { mState = state; }

        inline ScreenTransitionType getTransitionType() { return mType; }
        inline void setType(ScreenTransitionType type) { mType = type; }
        
        inline s32 getLength() { return mLength; }
        inline void setLength(s32 length) { mLength = length; }
    private:
        u32 mState;
        ScreenTransitionType mType;
        s32 mLength;
};

extern ScreenTransitionCtrl sScreenTransitionCtrl;

#endif
