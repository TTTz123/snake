#include <stdio.h>
#include <pthread.h>

void* func1()
{
	while(1){
		printf("this is func 1\n");
		sleep(1);
	}
}

void* func2()
{
	while(1){
		printf("this is func 2\n");
		sleep(1);
	}
}

int main()
{
	pthread_t th1;
	pthread_t th2;

	pthread_create(&th1, NULL, func1, NULL );
	pthread_create(&th2, NULL, func2, NULL );


	while(1);
	return 0;
}
