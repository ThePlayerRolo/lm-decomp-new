#ifndef EN_CHASE_HPP
#define EN_CHASE_HPP

#include "Sato/EnemyStrategy.hpp"

class EnChase : public EnemyStrategy {
public:
    EnChase();
    virtual ~EnChase() {};

    // From EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_1_Init();
    bool state_1_Behavior();
    bool state_2_Init();
    bool state_2_Behavior();
};

#endif
