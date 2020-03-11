#include "timewheel.h"
#include <unistd.h>
#include <stdio.h>

using namespace std;

TimeWheel::TimeWheel(int size, int tick):
  size_(size),
  tick_(tick),
  cur_index_(0) {

  time_wheel_.resize(size);
}

void TimeWheel::AddTimer(struct timeval &when, int64_t interval, bool periodic, function<void(void)>& cb) {
  shared_ptr<Timer> timer(new Timer);
  timer->when_ = when;
  timer->interval_ = interval;
  timer->periodic_ = periodic;
  timer->callback_ = cb;

  struct timeval now;
  gettimeofday(&now, nullptr);
  int64_t delay = when.tv_sec - now.tv_sec;
  if (delay < 0) {
    printf("too late to add timer\n");
    return;
  }
  int index = (delay / tick_ + cur_index_)%size_;
  time_wheel_[index].push_front(timer);
  printf("add timer at sec %ld, msec %ld\n", now.tv_sec, now.tv_usec/1000);
}

void TimeWheel::Tick() {
  // TODO
  cur_index_ = (cur_index_ + 1) % size_;
  struct timeval now;
  gettimeofday(&now, nullptr);
  int64_t cur_time_s = now.tv_sec;

  auto &timer_list = time_wheel_[cur_index_];
  auto it = timer_list.begin();
  vector<shared_ptr<Timer>> periodic_timers;

  while (it != timer_list.end()) {
  	auto &timer = *it;
  	// compare time
  	int64_t when = timer->when_.tv_sec;
     if (cur_time_s < when)
     	continue;

     timer->callback_();
     if (timer->periodic_) {
       periodic_timers.push_back(timer);
     }
     it = timer_list.erase(it);
  }

  for (auto &timer : periodic_timers) {
  	int64_t sec = timer->interval_;
    now.tv_sec += sec;
    AddTimer(now, timer->interval_, true, timer->callback_);
  }
}

