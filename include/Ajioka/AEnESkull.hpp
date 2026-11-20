#ifndef A_EN_E_SKULL_HPP
#define A_EN_E_SKULL_HPP

#include "Ajioka/AEnSkull.hpp"

class AEnESkull: public AEnSkull {
public:
    AEnESkull();
    virtual ~AEnESkull();

    // From AEnSkull -> EnGhostA -> EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From AEnSkull -> EnGhostA -> EnemyTypicalStrategy -> Koga::CharacterEventObserver
    virtual bool onCaptureBegin(Koga::CharacterEvent* msg);
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);

    // From AEnSkull -> EnGhostA
    virtual void EnGhostA_fn_800C8ECC();

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_0xA_Init();
    bool state_0xA_Behavior();
};

#endif
