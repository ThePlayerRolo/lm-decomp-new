#ifndef EN_HEY_MASK_HPP
#define EN_HEY_MASK_HPP

#include "Sato/EnemyStrategy.hpp"
#include "Sato/SaEnGenUtility.hpp"

class EnHeySpear : public EnemyStrategy {
public:
    EnHeySpear() {};
    virtual ~EnHeySpear() {};

    // From EnemyStrategy
    virtual void doBehavior();
};

class EnHeyMask : public EnemyStrategy, public SaEnZakoUtility {
public:
    EnHeyMask();
    virtual ~EnHeyMask() {};

    // From EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From SaEnZakoUtility
    virtual void vt_08();

    // From this class
    virtual void EnHeyMask_fn_800C6270();
    virtual void EnHeyMask_fn_800C62DC();

    
    //ptmf
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

class EnZenmai : public EnHeyMask {
public:
    EnZenmai() {};
    virtual ~EnZenmai() {};

    // From EnHeyMask -> EnemyStrategy
    virtual void doBehavior();
    virtual void doBehaviorInit();

    // From EnHeyMask
    virtual void EnHeyMask_fn_800C6270();
    virtual void EnHeyMask_fn_800C62DC();

    //ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_4_Init();
    bool state_4_Behavior();
};


#endif
