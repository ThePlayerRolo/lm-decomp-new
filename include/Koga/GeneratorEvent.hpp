#ifndef GENERATOR_EVENT_HPP
#define GENERATOR_EVENT_HPP

#include <types.h>

class EnThought;

// TODO: Maybe move this
class GeneratorEvent {
public:
    enum Message {
        /* 0x00 */ MESSAGE_0,
        /* 0x01 */ MESSAGE_1,
    };

    /* 0x00 */ Message mMessage;
    /* 0x04 */ EnThought* mThought;
    /* 0x08 */ u8* _8;
};

#endif
