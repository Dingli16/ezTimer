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
    int ret;

    ret = timer_task_create(my_timer_task, NULL, 1000, EZ_TIMER_MODE_LOOP);

    while(1)
    {
        sleep(2);
    }
    
    return 0;
}
