#ifndef ENEMY_TYPICAL_STRATEGY_H_
#define ENEMY_TYPICAL_STRATEGY_H_


#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyStrategy.hpp"


class EnemyTypicalStrategy: public EnemyStrategyDecorator,
                            public Koga::CharacterEventObserver {

public:
    EnemyTypicalStrategy() {};
    /* 0x08 */ virtual ~EnemyTypicalStrategy() { };

    /* 0x38 */ virtual bool onFishingBegin(Koga::CharacterEvent* msg);


private:
    /* 0x20 */ void* unk_20;
};



#endif
