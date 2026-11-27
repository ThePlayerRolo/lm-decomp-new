#ifndef ENCOND_STRATEGIES_HPP
#define ENCOND_STRATEGIES_HPP

#include "Sato/EnemyStrategy.hpp"

class CondAlwaysTrue : public EnemyStrategy {
public:
    CondAlwaysTrue() { }

    /* 0x1C */ virtual void doBehavior() { setNextState(256); }
};

class CondAppearAlpha : public EnemyStrategy {
public:
    CondAppearAlpha() { }

    /* 0x1C */ virtual void doBehavior();
    /* 0x20 */ virtual void doBehaviorInit();
};

class EnCondStrategies {
public:
    EnCondStrategies() : mCurStrategy(nullptr) {
    }

    EnemyStrategy* setCurrentStategy(u32 condType);

    /* 0x00 */ u8 _0[0x40];
    /* 0x40 */ EnemyStrategy* mCurStrategy;

    /* 0x8 */ virtual ~EnCondStrategies();
};

#endif
