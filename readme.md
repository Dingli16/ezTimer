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
```
Output:
```shell
my_timer_task: grow = 0
my_timer_task: grow = 1
my_timer_task: grow = 2
my_timer_task: grow = 3
my_timer_task: grow = 4
my_timer_task: grow = 5
my_timer_task: grow = 6
my_timer_task: grow = 7
my_timer_task: grow = 8
my_timer_task: grow = 9
my_timer_task: grow = 10
my_timer_task: grow = 11
my_timer_task: grow = 12
my_timer_task: grow = 13
my_timer_task: grow = 14
my_timer_task: grow = 15
timer task is stop.
```

## ToDo
- [x] 实现结束循环任务接口

