#ifndef A_EN_POLTERGEIST_HPP
#define A_EN_POLTERGEIST_HPP

#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyStrategy.hpp"

class AEnPoltergeist : public EnemyStrategy, public Koga::CharacterEventObserver {
public:
    AEnPoltergeist();
    virtual ~AEnPoltergeist();

    // From EnemyStrategy
    virtual bool vt_14();
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From Koga::CharacterEventObserver
    virtual bool onPlayerLeftRoom(Koga::CharacterEvent* msg);

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
};

#endif
