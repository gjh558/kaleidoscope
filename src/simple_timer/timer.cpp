#include "timer.h"
#include <sys/timerfd.h>
#include <iostream>
#include <time.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <assert.h>
using namespace std;

Timer::Timer():timewheel_(60, 1) {
	
}

void Timer::Start() {
  struct itimerspec new_value;
  struct timespec now;
  uint64_t exp;
  ssize_t s;

  int ret = clock_gettime(CLOCK_REALTIME, &now);//获取时钟时间
  assert(ret != -1);


  new_value.it_value.tv_sec = 1; //第一次到期的时间
  new_value.it_value.tv_nsec = now.tv_nsec; 

  new_value.it_interval.tv_sec = 1;      //之后每次到期的时间间隔
  new_value.it_interval.tv_nsec = 0;
  
  int timefd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
  ret = timerfd_settime(timefd, 0, &new_value, NULL);//启动定时器
  assert(ret != -1);

  cout << "timer started" << endl; // 定时器开启啦！

  int epollfd = epoll_create(1);  //创建epoll实例对象

  struct epoll_event ev;
  struct epoll_event events[20];
  ev.data.fd = timefd;
  ev.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, timefd, &ev); //添加到epoll事件集合

  for (; ;) 
  {
      int num = epoll_wait(epollfd, events, 20, 0);
      assert(num >= 0);

      for (int i = 0; i < num; i++) 
      {
          if (events[i].events & EPOLLIN) 
          {
              //....处理其他事件
              if (events[i].data.fd == timefd) 
              {
                  s = read(events[i].data.fd, &exp, sizeof(uint64_t)); //需要读出uint64_t大小, 不然会发生错误
                  assert(s == sizeof(uint64_t));
                  timewheel_.Tick();
              }
          }
      }
  }

  close(timefd);
  close(epollfd);
}

void Timer::RunAfter(int64_t delay, std::function<void(void)>& cb) {
	struct timeval now;
	gettimeofday(&now, nullptr);
	now.tv_sec += delay;

	timewheel_.AddTimer(now, 0, false, cb);
}

void Timer::RunEvery(int64_t interval, std::function<void(void)>& cb) {
	struct timeval now;
	gettimeofday(&now, nullptr);
	now.tv_sec += interval;
	timewheel_.AddTimer(now, interval, true, cb);
}
