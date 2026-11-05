#ifndef DISC_THREAD_HPP
#define DISC_THREAD_HPP

#include <types.h>

struct DiscFileInfo;
struct DiscThread;

void initDiscThread();
void sendDiscRequest(DiscFileInfo*);
void* createDvdThreadCallback(void*);
void initDvdThread(DiscThread*);

#endif
