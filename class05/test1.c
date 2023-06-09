#include <stdio.h>
#include <pthread.h>
void *thread(void *arg)
{
    printf("This is a thread and arg = %d.\n", *(int *)arg); // 用arg的指针变量来接
    *(int *)arg = 0;                                         // 因为传的时候为空变量 所以要强制转换成整形的指针
    return arg;
}
int main(int argc, char *argv[])
{
    pthread_t th;
    int ret;
    int arg = 10;
    int *thread_ret = NULL;
    ret = pthread_create(&th, NULL, thread, &arg); // 传了个arg地址过去
    if (ret != 0)
    {
        printf("Create thread error!\n");
        return -1;
    }
    printf("This is the main process.\n");
    pthread_join(th, (void **)&thread_ret);
    printf("thread_ret = %d.\n", *thread_ret); // 处理完后就是把原来的指针的内改成0
    return 0;
}
