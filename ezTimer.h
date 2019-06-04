#ifndef __eztimer_h__
#define __eztimer_h__
#include <pthread.h>

typedef void(*task_callback)(void *);

typedef enum {
    EZ_TIMER_MODE_ONCE,
    EZ_TIMER_MODE_LOOP,
}ez_timer_mode;

typedef struct{
    task_callback callback_fun; //事件回调
    void *param; //callback 所需参数
    unsigned int tick;  //callback 执行的周期,单位为毫秒
    ez_timer_mode mode;
}task_action;

typedef struct{
    pthread_t tid;
}ez_task;

ez_task* timer_task_create(task_callback cb, void *param, unsigned int tick, ez_timer_mode mode);
int timer_task_stop(ez_task *ezs);
#endif // __eztimer_h__
