#ifndef EN_CIRCLE_MOVE_HPP
#define EN_CIRCLE_MOVE_HPP

#include "Sato/EnemyStrategy.hpp"

class EnCircleMove : public EnemyStrategy {
public:
    EnCircleMove();
    virtual ~EnCircleMove();

    // From EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
};

#endif
