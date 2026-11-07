#ifndef BACKGROUND_TASK_HPP
#define BACKGROUND_TASK_HPP

#include <types.h>

typedef void (*BackgroundTaskFunc)();

void initBackgroundTask();
void startBackgroundTask(BackgroundTaskFunc);
s32 pollBackgroundTaskComplete();

#endif
