#ifndef A_EN_ITEMS_HPP
#define A_EN_ITEMS_HPP

#include "Sato/EnItems.hpp"
class AEnNegativeItemRandom : public EnNegativeItem {
public: 
    AEnNegativeItemRandom();
    virtual ~AEnNegativeItemRandom() {};

    // From EnNegativeItem -> EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
};

class AEnHeartItemEscape : public EnHeartItem {
public: 
    AEnHeartItemEscape();
    virtual ~AEnHeartItemEscape() {};

    // From EnHeartItem -> EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
};

class AEnItemBomb : public EnFiniteItem {
public: 
    AEnItemBomb();
    virtual ~AEnItemBomb();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem -> EnemyStrategy
    virtual void doBehavior();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem -> Koga::CharacterEventObserver
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);
    virtual bool onSprayedWithFire(Koga::CharacterEvent* msg);
    virtual bool onSprayedWithWater(Koga::CharacterEvent* msg);

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();

    // From EnFiniteItem
    virtual bool EnFiniteItem_fn_800D1318();    
};

#endif
