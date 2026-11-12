#ifndef A_EN_E_BONE_HPP
#define A_EN_E_BONE_HPP

#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyStrategy.hpp"

class AEnEBone : public EnemyStrategy, public Koga::CharacterEventObserver {
public:
    AEnEBone() { };
    virtual ~AEnEBone();

    // From EnemyStrategy
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
};

#endif
