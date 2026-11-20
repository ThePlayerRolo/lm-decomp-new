#ifndef EN_ITEMS_HPP
#define EN_ITEMS_HPP
#include "Koga/CharacterEventObserver.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "Sato/SaEnGenUtility.hpp"

class EnItem : public EnemyStrategy, public Koga::CharacterEventObserver {
public:
    EnItem();
    virtual ~EnItem();

    // From EnemyStrategy
    virtual void doBehavior(); // fn_800CFB5C
    virtual void doBehaviorInit(); // fn_800CFBC0

    // From Koga::CharacterEventObserver
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg); // fn_800D04A4
    virtual bool onPlayerLeftRoom(Koga::CharacterEvent* msg); // fn_800CFC6C

    // From this class
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();
    virtual bool EnItem_fn_800D00B4();

    // ptmf
    bool state_0_Init();
    bool state_0_Behavior();
    bool state_1_Init();
    bool state_1_Behavior();
    bool state_2_Init();
    bool state_2_Behavior();
    bool state_3_Init();
    bool state_3_Behavior();
};

class EnItemThrowUp : public EnItem {
public:
    EnItemThrowUp();

    // From EnItem
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();

    // From this class
    virtual void EnItemThrowUp_fn_800D036C();

    virtual ~EnItemThrowUp();
};

class EnFiniteItem : public EnItemThrowUp, private SaEnZakoUtility {
public:
    EnFiniteItem();

    // From SaEnZakoUtility
    virtual void vt_08();

    // From this class
    virtual void EnFiniteItem_fn_800D1300();
    virtual void EnFiniteItem_fn_800D12E8();
    virtual bool EnFiniteItem_fn_800D1318();

    virtual ~EnFiniteItem();
};

class EnHeartItem : public EnFiniteItem {
public:
    EnHeartItem() {};
    virtual ~EnHeartItem();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem -> EnemyStrategy
    virtual void init();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();
    
    // From EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
};

class EnJewel : public EnFiniteItem {
public:
    EnJewel() {};
    virtual ~EnJewel();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();
    
    // From EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
};

class EnPearl : public EnJewel {
public:
    EnPearl();
    virtual ~EnPearl() {};

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual bool EnItem_fn_800D00B4();
};

class EnGold : public EnJewel {
public:
    EnGold() {};
    virtual ~EnGold() {};

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
};

class EnElementJewel : public EnJewel {
public:
    EnElementJewel();
    virtual ~EnElementJewel();

    
    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem -> Koga::CharacterEventObserver
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00B0();

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();

    // From EnJewel -> EnFiniteItem 
    virtual bool EnFiniteItem_fn_800D1318();
};

class EnCrown : public EnJewel {
public:
    EnCrown() {};
    virtual ~EnCrown() {};

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
    
    // From EnJewel -> EnFiniteItem 
    virtual bool EnFiniteItem_fn_800D1318();
};

class EnNegativeItem : public EnFiniteItem {
public:
    EnNegativeItem() {};
    virtual ~EnNegativeItem() {};

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
};

class EnMarioItem : public EnFiniteItem {
public:
    EnMarioItem() {};
    virtual ~EnMarioItem() {};

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
    
    // From EnJewel -> EnFiniteItem 
    virtual bool EnFiniteItem_fn_800D1318();
};

class EnKey : public EnFiniteItem {
public:
    EnKey();
    virtual ~EnKey() {};

    // From EnFiniteItem -> EnItemThrowUp -> EnItem -> Koga::CharacterEventObserver
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void EnItem_fn_800CFFD8();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void EnItemThrowUp_fn_800D036C();
    
    // From EnJewel -> EnFiniteItem 
    virtual bool EnFiniteItem_fn_800D1318();
};

#endif
