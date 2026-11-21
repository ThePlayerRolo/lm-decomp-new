#ifndef EN_CIRCLE_MOVE_HPP
#define EN_CIRCLE_MOVE_HPP

#include "Sato/EnemyStrategy.hpp"

class EnCircleMove : public EnemyStrategy {
public:
    EnCircleMove() { }
    virtual ~EnCircleMove();

    // From EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();

public:
    /* 0x14 */ s32 _14;
    /* 0x18 */ f32 _18;
    /* 0x1C */ f32 _1C;
    /* 0x20 */ f32 _20;
};

#endif
