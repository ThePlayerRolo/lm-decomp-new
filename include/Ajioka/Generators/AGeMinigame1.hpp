#ifndef A_GE_MINIGAME_1_HPP
#define A_GE_MINIGAME_1_HPP

#include "Koga/Observer.hpp"
#include "Sato/EnemyStrategy.hpp"

struct GeneratorEvent;

class AGeMinigame1 : public EnemyStrategy, public Koga::Observer<GeneratorEvent, void> {
public:
    AGeMinigame1();
    virtual ~AGeMinigame1();

    // From EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From Koga::Observer
    virtual void receiveMessage(GeneratorEvent* msg);

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_0x104_Init();
    bool state_0x104_Behavior();
    bool state_0x103_Init();
    bool state_0x103_Behavior();
    bool state_0x106_Init();
    bool state_0x106_Behavior();
    bool state_0x107_Init();
    bool state_0x107_Behavior();
};

#endif
