#ifndef ENEMY_STRATEGY_H_
#define ENEMY_STRATEGY_H_

#include <types.h>
#include <JSystem/JORReflexible.hpp>

class EnemyStrategy;
class EnZako; 

typedef void* (EnemyStrategyInitFn)(void* buffer, u32 bufferSize);
typedef bool (EnemyStrategy::*EnemyStrategyStateFn)();

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
