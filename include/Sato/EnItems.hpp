#ifndef EN_ITEMS_HPP
#define EN_ITEMS_HPP

#include "Koga/CharacterEventObserver.hpp"
#include "Koga/ToolData.hpp"
#include "Sato/EnemyStrategy.hpp"
#include "Sato/SaEnGenUtility.hpp"
#include "Koga/EnCondStrategies.hpp"
#include "Koga/EnThrowUp.hpp"

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
    virtual void initItemParams();
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

    // Gets the strategy used for checking if the item can appear.
    EnemyStrategy* getCondStrategy(s32);
    // Gets the strategy used for checking if the item should appear.
    EnemyStrategy* getAppearStrategy(s32);

    bool fn_800CFFDC();
    bool fn_800D0070();

    void fn_800D00BC();
    void fn_800D01EC();

    /* 0x18 */ CondAlwaysTrue mAlwaysTrueCond;
    /* 0x2C */ EnCondStrategies mCondStrategies;
    /* 0x74 */ CondAppearAlpha mAppearAlphaCond;
    /* 0x88 */ EnemyStrategy* _88;
    /* 0x8C */ EnemyStrategy* _8C;
    /* 0x90 */ bool _90;
    /* 0x91 */ u8 _91;
    /* 0x94 */ s32 _94;
    /* 0x98 */ ToolDataRef _98;
};

class EnItemThrowUp : public EnItem {
public:
    EnItemThrowUp() { }

    // From EnItem
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();

    // From this class
    virtual void onThrowUp();

    /* 0x0A0 */ EnThrowUp mThrowUp;
    /* 0x144 */ s32 mThrowCount;
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

    /* 0x1AC */ s32 _1AC;
    /* 0x1B0 */ s32 _1B0;
    /* 0x1B4 */ TParams mParams;
    /* 0x1C0 */ TParamT<s32> mIgnoreTime;
    /* 0x1D4 */ TParamT<s32> mLife;
    /* 0x1E8 */ TParamT<s32> mBlinkFeq;
    /* 0x1FC */ TParamT<s32> mBlinkLife;
};

class EnHeartItem : public EnFiniteItem {
public:
    EnHeartItem() {};
    virtual ~EnHeartItem();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem -> EnemyStrategy
    virtual void init();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();
};

class EnJewel : public EnFiniteItem {
public:
    EnJewel() {};
    virtual ~EnJewel();

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();
};

class EnPearl : public EnJewel {
public:
    EnPearl();
    virtual ~EnPearl() {};

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual bool EnItem_fn_800D00B4();
};

class EnGold : public EnJewel {
public:
    EnGold() {};
    virtual ~EnGold() {};

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();
};

class EnElementJewel : public EnJewel {
public:
    EnElementJewel();
    virtual ~EnElementJewel();


    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem -> Koga::CharacterEventObserver
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual void EnItem_fn_800D00B0();

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();

    // From EnJewel -> EnFiniteItem
    virtual bool EnFiniteItem_fn_800D1318();
};

class EnCrown : public EnJewel {
public:
    EnCrown() {};
    virtual ~EnCrown() {};

    // From EnJewel -> EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();

    // From EnJewel -> EnFiniteItem
    virtual bool EnFiniteItem_fn_800D1318();
};

class EnNegativeItem : public EnFiniteItem {
public:
    EnNegativeItem() {};
    virtual ~EnNegativeItem() {};

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();
};

class EnMarioItem : public EnFiniteItem {
public:
    EnMarioItem() {};
    virtual ~EnMarioItem() {};

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();

    // From EnJewel -> EnFiniteItem
    virtual bool EnFiniteItem_fn_800D1318();
};

class EnKeyParams {
public:
    EnKeyParams() :
        mParams("/param/th/EnKey.prm"),
        PARAM_INIT(sIgnoreColFrame, 10.0f)
    { }
public:
    /* 0x0 */ TParams mParams;
    /* 0xC */ TParamT<f32> sIgnoreColFrame;
};


class EnKey : public EnFiniteItem {
public:
    EnKey();
    virtual ~EnKey() {};

    // From EnFiniteItem -> EnItemThrowUp -> EnItem -> Koga::CharacterEventObserver
    virtual bool onCaptureEnd(Koga::CharacterEvent* msg);

    // From EnFiniteItem -> EnItemThrowUp -> EnItem
    virtual void initItemParams();
    virtual void EnItem_fn_800D00A8();
    virtual void EnItem_fn_800D00AC();
    virtual void EnItem_fn_800D00B0();

    // From EnFiniteItem -> EnItemThrowUp
    virtual void onThrowUp();

    // From EnJewel -> EnFiniteItem
    virtual bool EnFiniteItem_fn_800D1318();
public:
    static EnKeyParams sParams;
public:
    /* 0x210 */ bool _210;
};

#endif
