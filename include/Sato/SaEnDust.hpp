#ifndef SA_EN_DUST
#define SA_EN_DUST

#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyTypicalStrategy.hpp"
class SaEnDust : public EnemyTypicalStrategy, public Koga::CharacterEvent {
public:
    SaEnDust();
    virtual ~SaEnDust();

    // From EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    //ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_1_Init();
    bool state_1_Behavior();
};
#endif
