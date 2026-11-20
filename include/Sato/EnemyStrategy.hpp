#ifndef ENEMY_STRATEGY_H_
#define ENEMY_STRATEGY_H_

#include <types.h>
#include <JSystem/JORReflexible.hpp>

class EnemyStrategy;
class EnZako; 

typedef void* (EnemyStrategyInitFn)(void* buffer, u32 bufferSize);
typedef bool (EnemyStrategy::*EnemyStrategyStateFn)();

enum STRATEGY_STATE {
    STRAT_STATE_0   = 0x0,
    STRAT_STATE_1   = 0x1,
    STRAT_STATE_2   = 0x2,
    STRAT_STATE_3   = 0x3,
    STRAT_STATE_4   = 0x4,
    STRAT_STATE_5   = 0x5,
    STRAT_STATE_6   = 0x6,
    STRAT_STATE_7   = 0x7,
    STRAT_STATE_8   = 0x8,
    STRAT_STATE_9   = 0x9,
    STRAT_STATE_A   = 0xA,
    STRAT_STATE_B   = 0xB,
    STRAT_STATE_C   = 0xC,
    STRAT_STATE_D   = 0xD,
    STRAT_STATE_E   = 0xE,
    STRAT_STATE_F   = 0xF,
    STRAT_STATE_10  = 0x10,
    STRAT_STATE_11  = 0x11,
    STRAT_STATE_12  = 0x12,
    STRAT_STATE_13  = 0x13,
    STRAT_STATE_14  = 0x14,
    STRAT_STATE_15  = 0x15,
    STRAT_STATE_16  = 0x16,
    STRAT_STATE_17  = 0x17,
    STRAT_STATE_18  = 0x18,
    STRAT_STATE_19  = 0x19,
    STRAT_STATE_1A  = 0x1A,
    STRAT_STATE_1B  = 0x1B,
    
    // 0x100+ 
    // Seems to be used in attacks classes
    STRAT_STATE_100 = 0x100,
    STRAT_STATE_101 = 0x101,
    STRAT_STATE_102 = 0x102,

    // Seems to be used in generators classes
    STRAT_STATE_103 = 0x103,
    STRAT_STATE_104 = 0x104,
    STRAT_STATE_105 = 0x105,
    STRAT_STATE_106 = 0x106,
    STRAT_STATE_107 = 0x107,
};

// Each EnemyStrategy implementation has a static array of these structures.
// In their doBehavior and doBehaviorInit functions, they search for an entry
// with a stateIndex that matches their mCurrentState.
struct EnemyStrategyState {
    /* 0x00 */ u16 mStateIndex;
    /* 0x04 */ EnemyStrategyStateFn mBehaviorInitFunc; // Called in overrides of EnemyStrategy::doBehaviorInit
    /* 0x10 */ EnemyStrategyStateFn mBehaviorFunc; // Called in overrides of EnemyStrategy::doBehavior
};

class EnemyStrategy : public JORReflexible {
public:
    EnemyStrategy();
    /* 0x08 */ virtual ~EnemyStrategy();
    /* 0x0C */ virtual void init();
    /* 0x10 */ virtual void update();
    /* 0x14 */ virtual bool vt_14();
    /* 0x18 */ virtual void vt_18();
    /* 0x1C */ virtual void doBehavior();
    /* 0x20 */ virtual void doBehaviorInit();

    inline EnZako* getZako() const { return mpZako; }

    inline u16 getNextState() const { return mNextState; }
    inline u16 getCurrentState() const { return mCurrentState; }

    void setNextState(u16 state);
    void changeState();

    static EnemyStrategyInitFn** getInitFunction(u32 index);
    static void* allocStrategy(u32 classSize, void* buffer, u32 bufferSize);

    void operator delete(void* ptr) {
        noOpDelete(ptr);
    }
    
    /* 0x04 */ EnZako* mpZako;
    /* 0x08 */ void* mpUserData;
    
protected:
    /* 0x0C */ u16 mNextState; // 0xFFFF = end strategy
    /* 0x0E */ u16 mCurrentState;
    /* 0x10 */ u32 mTimer;
private:
    static void noOpDelete(void* ptr);
    static EnemyStrategyInitFn* sInitFunctions[187];
};

class EnemyStrategyDecorator : public EnemyStrategy {
public:
    EnemyStrategyDecorator();
    bool setTsuriStrategy(EnemyStrategy* strategy);

    virtual void update();
private:
    /* 0x14 */ EnemyStrategy* mTsuriStrategy;
    /* 0x18 */ u16 _18;
};

// Same body in every TU (in doBehavior)
inline EnemyStrategyState* findStrategyState(EnemyStrategyState* states, int count, u16 index) {
    for (EnemyStrategyState* state = &states[0]; state != &states[count]; state++) {
        if (state->mStateIndex == index) {
            return state;
        }
    }
    return nullptr;
}

#endif
