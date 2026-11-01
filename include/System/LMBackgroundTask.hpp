#ifndef LM_BACKGROUND_TASK_HPP
#define LM_BACKGROUND_TASK_HPP

#include <types.h>

typedef void (*LMBackgroundTaskCallback)();
struct BackgroundTask;

namespace LMBackgroundTask {
    void init();
    void start(LMBackgroundTaskCallback);
    s32 pollDone();
    void* createThreadCallback(void*);
    void initBackgroundTaskInternal(BackgroundTask*);
};

#endif
