#ifndef SA_EN_GEN_UTILITY_HPP
#define SA_EN_GEN_UTILITY_HPP

#include "JSystem/JORReflexible.hpp"
#include "Koga/Observer.hpp"
#include "Sato/EnemyStrategy.hpp"

struct GeneratorEvent;

// The first void is GeneratorEvent
class SaEnGenUtility: public EnemyStrategy, public Koga::Observer<GeneratorEvent, void> {
public:
    SaEnGenUtility();
    virtual ~SaEnGenUtility();

    virtual void receiveMessage(GeneratorEvent* msg) = 0;
};

class SaEnZakoUtility {
private:
    /* 0x00 */ void* _00;
    /* 0x04 */ void* _04;
    /* 0x08 */ void* _08;
    /* 0x0c */ bool _0c;
    /* 0x0d - 0x41 */ u8 _0d[0x41-0xd];
    /* 0x41 */ u8 _41;
    /* 0x42- 0x41 */ u8 _42[0x60-0x42];

public:
    SaEnZakoUtility();

    virtual void vt_08() = 0;
    virtual ~SaEnZakoUtility();

    /* probably a setter */ void fn_80143810(void* param1, void* param2);
}; 


#endif
