#ifndef BACKGROUND_TASK_HPP
#define BACKGROUND_TASK_HPP

#include <types.h>

typedef void (*BackgroundTaskFunc)();
struct BackgroundTask;

void initBackgroundTask();
void startBackgroundTask(BackgroundTaskFunc);
s32 pollBackgroundTaskComplete();
void* createBackgroundTaskThreadCallback(void*);
void initBackgroundTaskInternal(BackgroundTask*);

#endif
