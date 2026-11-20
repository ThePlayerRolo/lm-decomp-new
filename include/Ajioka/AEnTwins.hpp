#ifndef A_EN_TWINS_HPP
#define A_EN_TWINS_HPP

#include "Sato/EnemyTypicalStrategy.hpp"
class AEnTwins : public EnemyTypicalStrategy {
public:
    AEnTwins();
    virtual ~AEnTwins();

    // From EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual bool vt_14();
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From EnemyTypicalStrategy -> Koga::CharacterEventObserver
    virtual bool onCollideWithPlayer(Koga::CharacterEvent* msg);
    virtual bool onPlayerLeftRoom(Koga::CharacterEvent* msg);
    virtual bool onEnteredFlashlightBeam(Koga::CharacterEvent* msg);
    virtual bool onFishingBegin(Koga::CharacterEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_1_Init();
    bool state_1_Behavior();
    bool state_2_Init();
    bool state_2_Behavior();
    bool state_3_Init();
    bool state_3_Behavior();
    bool state_4_Init();
    bool state_4_Behavior();
    bool state_5_Init();
    bool state_5_Behavior();
    bool state_6_Init();
    bool state_6_Behavior();
    bool state_7_Init();
    bool state_7_Behavior();
    bool state_8_Init();
    bool state_8_Behavior();
    bool state_9_Init();
    bool state_9_Behavior();
    bool state_A_Init();
    bool state_A_Behavior();
};

#endif
