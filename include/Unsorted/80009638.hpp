#ifndef _80009638_H_
#define _80009638_H_

#include "Unsorted/MathUtils.hpp"
#include <types.h>

//This seems to be a common use of fn_80009638 that happens to cast it to s32
inline s32 randomIntModulate(s32 val) {
    return randomInt() % val;
}
#endif
