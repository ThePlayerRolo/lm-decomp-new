#ifndef SA_EN_DANCER_2_HPP
#define SA_EN_DANCER_2_HPP

#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyTypicalStrategy.hpp"

class SaEnDancer2 : public EnemyTypicalStrategy, public Koga::CharacterEvent {
public:
    SaEnDancer2();
    virtual ~SaEnDancer2();

    // From EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From EnemyTypicalStrategy -> Koga::CharacterEventObserver
    virtual bool onCaptureBegin(CharacterEvent* msg);
    virtual bool onCaptureEnd(CharacterEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
};

#endif
