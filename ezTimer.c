//通用的定时任务
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ezTimer.h"

static void *task_loop(void *data)
{
    task_action act;
    int count = 0;

    memcpy(&act, data, sizeof(task_action));
    while(1)
    {
        pthread_testcancel();
        if(count % act.tick == 0)
        {
            act.callback_fun(act.param);
            if(act.mode == EZ_TIMER_MODE_ONCE)
            {
                break;
            }
        }
        count++;
        usleep(1000); // 1毫秒
    }

    return NULL;
}

int timer_task_stop(ez_task *ezt)
{
    return pthread_cancel(ezt->tid);
}

/***********************************************************
 * cb    -- 定时执行的任务回调
 * param -- 回调参数,如果不需要可以填NULL
 * tick  -- 定时执行的周期
 **********************************************************/
ez_task* timer_task_create(task_callback cb, void *param, unsigned int tick, ez_timer_mode mode)
{
    pthread_t tid;
    task_action action;
    int ret;
    ez_task *ezt; 
    if(cb == NULL || tick == 0)
    {
        printf("param not valid.\n");
        goto ERROR0;
    }

    ezt = calloc(1, sizeof(ez_task));
    if(NULL == ezt)
    {
        printf("calloc fail.\n");
        goto ERROR0;
    }

    action.callback_fun = cb;
    action.param = param;
    action.tick = tick;
    action.mode = mode;

    ret = pthread_create(&ezt->tid, NULL, task_loop, &action);
    if(ret != 0)
    {
        perror("pthreae_create");
        goto ERROR1;
    }
    pthread_detach(ezt->tid);

    return ezt;

    ERROR1:
        free(ezt);
    ERROR0:
        return NULL;
}

