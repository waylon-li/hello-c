#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct _mtimer_t {
	timer_t timerid;
	int sec;
	int nsec;
	uint8_t once;
	uint8_t flag;
	struct timeval lasttv;
	struct timeval curtv;
	int64_t deltam;
} mtimer_t;


mtimer_t mtimer = {0};


static void print_time(struct timeval tv)
{
	struct tm *p_tm;
	p_tm = gmtime(&tv.tv_sec);
	printf("time: %04d%02d%02d%02d%02d%02d, usec: %06ld\n",
		1900 + p_tm->tm_year, 1 + p_tm->tm_mon, p_tm->tm_mday,
		p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec, tv.tv_usec);
}

static int mtimer_start()
{
	struct itimerspec it;
	it.it_interval.tv_sec = mtimer.sec;
	it.it_interval.tv_nsec = mtimer.nsec;
	it.it_value.tv_sec = mtimer.sec;		
	it.it_value.tv_nsec = mtimer.nsec;

	if (timer_settime(mtimer.timerid, 0, &it, NULL) == -1) {
		printf("fail to timer_settime\n");
		return -1;
	}
	
	return 0;
}

static int mtimer_stop()
{
	struct itimerspec it;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_nsec = 0;
	it.it_value.tv_sec = 0;		
	it.it_value.tv_nsec = 0;

	if (timer_settime(mtimer.timerid, 0, &it, NULL) == -1) {
		printf("fail to timer_settime\n");
		return -1;
	}
	
	return 0;
}

static void mtimer_thread(union sigval v)
{
	mtimer_t *mt = (mtimer_t *)v.sival_ptr;
		
	struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
	int64_t curm = cur_time.tv_sec*1000 + cur_time.tv_usec/1000;
	int64_t lastm = mt->curtv.tv_sec*1000 + mt->curtv.tv_usec/1000;
	if (curm - lastm > mt->deltam || curm - lastm < -mt->deltam) {
		mtimer_stop();	
		if (mt->once != 1)
			mt->once = 1;
		mt->flag = 1;
	}
	mt->lasttv.tv_sec = mt->curtv.tv_sec;
	mt->lasttv.tv_usec = mt->curtv.tv_usec;
	mt->curtv.tv_sec = cur_time.tv_sec;
	mt->curtv.tv_usec = cur_time.tv_usec;
	
	print_time(cur_time);
}

int mtimer_init()
{
	// XXX int timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid);
	// clockid--值：CLOCK_REALTIME,CLOCK_MONOTONIC,CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID
	// evp--存放环境值的地址,结构成员说明了定时器到期的通知方式和处理方式等
	// timerid--定时器标识符
	struct sigevent evp;
	memset(&evp, 0, sizeof(struct sigevent));	//清零初始化
	evp.sigev_notify = SIGEV_THREAD;			//线程通知的方式，派驻新线程
	evp.sigev_notify_function = mtimer_thread;	//线程函数地址
	evp.sigev_value.sival_ptr = (void *)&mtimer;				//线程函数参数
 
	if (timer_create(CLOCK_REALTIME, &evp, &mtimer.timerid) == -1) {
		printf("fail to timer_create");
		return -1;
	}
	
	return 0;	
}

int mtimer_set(int sec, int nsec, int deltam)
{
	// XXX int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,struct itimerspec *old_value);
	// timerid--定时器标识
	// flags--0表示相对时间，1表示绝对时间，通常使用相对时间
	// new_value--定时器的新初始值和间隔，如下面的it
	// old_value--取值通常为0，即第四个参数常为NULL,若不为NULL，则返回定时器的前一个值
	
	//第一次间隔it.it_value这么长,以后每次都是it.it_interval这么长,就是说it.it_value变0的时候会装载it.it_interval的值
	//it.it_interval可以理解为周期
	struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
	mtimer.lasttv.tv_sec = cur_time.tv_sec;
	mtimer.lasttv.tv_usec = cur_time.tv_usec;
	mtimer.curtv.tv_sec = cur_time.tv_sec;
	mtimer.curtv.tv_usec = cur_time.tv_usec;
	mtimer.sec = sec;	
	mtimer.nsec = nsec;	
	mtimer.deltam = deltam;	
		
	mtimer_start();

	return 0;
}

int mtimer_reset()
{
	struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
	mtimer.lasttv.tv_sec = cur_time.tv_sec;
	mtimer.lasttv.tv_usec = cur_time.tv_usec;
	mtimer.curtv.tv_sec = cur_time.tv_sec;
	mtimer.curtv.tv_usec = cur_time.tv_usec;
	mtimer.flag = 0;
	
	struct itimerspec it;
	it.it_interval.tv_sec = mtimer.sec;
	it.it_interval.tv_nsec = mtimer.nsec;
	it.it_value.tv_sec = mtimer.sec;		
	it.it_value.tv_nsec = mtimer.nsec;		

	if (timer_settime(mtimer.timerid, 0, &it, NULL) == -1) {
		printf("fail to timer_settime\n");
		return -1;
	}
}

int mtimer_get_once()
{
	return mtimer.once; 
}

int mtimer_get_flag(int64_t *delta_msec)
{
	int ret = timer_getoverrun(mtimer.timerid);
	if (ret != 0) {
		printf("getoverrun ret: %d\n", ret);
		return -3;
	}

	if (delta_msec == NULL) {
		printf("delta_msec is NULL\n");
		return -2;
	}

	if (mtimer.flag != 1)
		return -2;

	int64_t curm = mtimer.curtv.tv_sec*1000 + mtimer.curtv.tv_usec/1000;
	int64_t lastm = mtimer.lasttv.tv_sec*1000 + mtimer.lasttv.tv_usec/1000;	
	*delta_msec = curm - lastm;

	return 0; 
}

int mtime_exit()
{
	return timer_delete(mtimer.timerid);
}
 
int main()
{
	mtimer_init();	
	mtimer_set(1, 0, 2000);	
#if 1
	for (;;) {
		usleep(100*1000);
		int64_t m_sec = 0;
		if (mtimer_get_flag(&m_sec) == 0) {
			printf("sec: %ld, msec: %ld\n", m_sec/1000, m_sec%1000);
			mtimer_reset();
		}	
	}
#endif	
	mtime_exit();	
	pause();
 
	return 0;
}


