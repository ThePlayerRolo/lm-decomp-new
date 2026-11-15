#ifndef SA_EN_CANDLE_HPP
#define SA_EN_CANDLE_HPP

#include "Sato/EnemyTypicalStrategy.hpp"
class SaEnCandle : public EnemyTypicalStrategy, public Koga::CharacterEvent {
public:
    SaEnCandle();
    virtual ~SaEnCandle();

    // From EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From EnemyTypicalStrategy -> Koga::CharacterEventObserver
    virtual bool onCaptureBegin(Koga::CharacterEvent* msg);
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
};

#endif
