#ifndef DISC_THREAD_HPP
#define DISC_THREAD_HPP

#include <types.h>

class DiscFileInfo;
struct DiscThread;

void initDiscThread();
void sendDiscRequest(DiscFileInfo*);
void createDvdThreadCallback(DiscThread*);
void initDvdThread(DiscThread*);

#endif
