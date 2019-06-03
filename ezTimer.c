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

        //todo: 提供退出结束机制
    }

    return NULL;
}

/***********************************************************
 * cb    -- 定时执行的任务回调
 * param -- 回调参数,如果不需要可以填NULL
 * tick  -- 定时执行的周期
 **********************************************************/
int timer_task_create(task_callback cb, void *param, unsigned int tick, ez_timer_mode mode)
{
    pthread_t tid;
    task_action action;
    int ret;

    if(cb == NULL || tick == 0)
    {
        printf("param not valid.\n");
        return -1;
    }
    action.callback_fun = cb;
    action.param = param;
    action.tick = tick;
    action.mode = mode;

    ret = pthread_create(&tid, NULL, task_loop, &action);
    if(ret != 0)
    {
        perror("pthreae_create");
        return -1;
    }
    pthread_detach(tid);

    return 0;
}

