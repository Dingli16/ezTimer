#include <stdio.h>
#include <unistd.h>
#include "ezTimer.h"

void my_timer_task(void *param) //周期性打印自增数字
{
    static int grow = 0;
    printf("my_timer_task: grow = %d\n", grow++);
}

int main(int argc, char *argv[])
{
    ez_task *ezt;

    ezt = timer_task_create(my_timer_task, NULL, 1000, EZ_TIMER_MODE_LOOP);
    if(NULL == ezt)
    {
        printf("create timer task fail.\n");
        return -1;
    }

    while(1)
    {
        // 20s 后取消定时任务,如果需要一直运行下去，无需停止
        sleep(20);
        timer_task_stop(ezt);
        printf("timer task is stop.\n");
        break;
    }
    
    return 0;
}
