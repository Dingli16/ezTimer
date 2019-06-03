## 简介
基于Posix pthread实现定时任务

## 特性
- 回调机制，耦合度低
- posix pthread
- 接口简单

## 示例
```c
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

    //创建定时任务
    ret = timer_task_create(my_timer_task, NULL, 1000, EZ_TIMER_MODE_LOOP);

    while(1)
    {
        sleep(2);
    }

    return 0;
}
```

## ToDo
- 实现结束循环任务接口

