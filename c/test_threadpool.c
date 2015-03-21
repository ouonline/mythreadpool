#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

static void print(void* arg)
{
    printf("%s\n", (const char*)arg);
}

int main(void)
{
    const char* str = "Hello, world!";
    struct threadpool* tp;

    tp = threadpool_init(5);
    if (!tp)
        return 0;

    printf("thread num = %u\n", threadpool_size(tp));
    threadpool_add_task(tp, (void*)str, print, NULL);

    threadpool_del_thread(tp, 2);
    sleep(1);
    printf("thread num = %u\n", threadpool_size(tp));

    threadpool_add_thread(tp, 5);
    sleep(1);
    printf("thread num = %u\n", threadpool_size(tp));

    threadpool_destroy(tp);

    return 0;
}
