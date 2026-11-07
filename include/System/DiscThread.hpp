#ifndef DISC_THREAD_HPP
#define DISC_THREAD_HPP

#include <dolphin/os/OSMessage.h>
#include <types.h>

struct DiscFileInfo;

void initDiscThread();
void sendDiscRequest(DiscFileInfo*);

#endif
