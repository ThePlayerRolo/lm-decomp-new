#ifndef A_EN_TOY_HPP
#define A_EN_TOY_HPP

#include "Sato/EnHeyMask.hpp"
class AEnToy : public EnHeyMask {
public:
    AEnToy();
    virtual ~AEnToy();

    
    // From EnHeyMask -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From EnHeyMask
    virtual void EnHeyMask_fn_800C62DC();
    
    //ptmf
    bool state_0_Init();
    bool state_0_Behavior();
};

#endif
