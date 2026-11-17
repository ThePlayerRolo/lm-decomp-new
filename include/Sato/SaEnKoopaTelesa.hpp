#ifndef SA_EN_KOOPA_TELESA_HPP
#define SA_EN_KOOPA_TELESA_HPP

#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyTypicalStrategy.hpp"
#include "Sato/SaEnTelesaBase.hpp"

class SaEnKoopaTelesa: public EnemyTypicalStrategy, public Koga::CharacterEvent, public SaEnTelesaBase  {
public:
    SaEnKoopaTelesa();
    virtual ~SaEnKoopaTelesa();

    // From EnemyTypicalStrategy -> EnemyStrategyDecorator -> EnemyStrategy
    virtual bool vt_14();
    virtual void doBehavior();
    virtual void doBehaviorInit();

    
    // From EnemyTypicalStrategy -> Koga::CharacterEventObserver
    virtual bool onCollideWithPlayer(CharacterEvent* msg);
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);
    virtual bool onCaptureBegin(Koga::CharacterEvent* msg);

    // From SaEnTelesaBase -> SaEnZakoUtility 
    virtual void vt_08();

    // From SaEnTelesaBase
    virtual void SaEnTelesaBase_vt_0F();
    virtual void SaEnTelesaBase_vt_14();


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
