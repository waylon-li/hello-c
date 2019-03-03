/************************************************************************
	> File Name: ./threadtry.c
	> Author: linuxidc
	> Mail: linuxidc@linuxidc.com 
	> Created Time: 2018年07月15日 星期日 15时32分16秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>


static int quit_signal = 0;


void *func_three(void *arg)
{
	printf("new thread three.\n");

	/* 分离自我 */
	pthread_detach(pthread_self());

	for(;;){
		if(quit_signal){
			printf("goto thread_three_exit.\n");
			goto thread_three_exit;
		}
		printf("thread three runing.\n");
		sleep(3);
	}
thread_three_exit:
	printf("thread three exit.\n");
	pthread_exit(NULL);
}


void *func_two(void *arg)
{
	printf("new thread two.\n");

	/* 分离自我 */
	pthread_detach(pthread_self());
	
	int re;
	pthread_t pt_three;
	re = pthread_create(&pt_three, NULL, func_three, NULL);
	if(re != 0){
		printf("create thread one fail.\n");
		exit(-1);
	}
	
	for(;;){
		if(quit_signal){
			printf("goto thread_two_exit.\n");
			goto thread_two_exit;
		}
		printf("thread two runing.\n");
		sleep(3);
	}
thread_two_exit:
	printf("thread two exit.\n");
	pthread_exit(NULL);
}


void *func_one(void *arg)
{
	printf("new thread one.\n");
	printf("thread one exit.\n");
	sleep(3);
}


void stop_signal(int signal)
{
	printf("=============== stop signal =============\n");
	quit_signal = 1;
}


int main(int argc, char *argv[])
{
	int re;
	pthread_t pt_one, pt_two;

	signal(SIGINT, stop_signal);
	
	re = pthread_create(&pt_one, NULL, func_one, NULL);
	if(re != 0){
		printf("create thread one fail.\n");
		exit(-1);
	}

	re = pthread_create(&pt_two, NULL, func_two, NULL);
	if(re != 0){
		printf("create thread two fail.\n");
		exit(-1);
	}
	
	sleep(3);

//	re = pthread_join(pt_one, NULL);
//	re = pthread_join(pt_two, NULL);
	
	for(;;){
		if(quit_signal){
			sleep(3);
			printf("goto thread_main_exit.\n");
			goto thread_main_exit;
		}
		printf("thread main running.\n");
		sleep(3);
	}
thread_main_exit:
	printf("main thread exit.\n");
	return 0;
}
