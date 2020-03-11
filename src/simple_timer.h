#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_


using TimeStamp = struct timeval;
using TimerCallback = function<void(void*)>;
using TimerId = int64_t;

class TimerQueue {
 private:
  struct TimerEntry {
    function<void(void*)> timer_proc_;
    TimeStamp when_;
    void *private_data_;
    int64_t interval_;
    TimerId id_;
    bool periodic_;
  };

  std::map<TimerId, shared_ptr<TimerEntry>> timer_map_;
  std::vector<std::list<shared_ptr<TimerEntry>>> timer_queue_;
 public:
  TimerQueue(int timer_queue_capacity) timer_queue_(timer_queue_capacity) {
  }
  ~TimerQueue() {
    for (auto l : timer_queue_)
      l.clear();
  }

 private:
  TimerId AddTimer(TimerCallback &cb, TimeStamp when, int64_t interval, bool periodic);
  void Cancel(TimerId id);
  TimerId Id(TimeStamp when);
 public:
  friend void RunAt(const TimeStamp& when, const TimerCallback& cb);
  friend void RunAfter(const int64_t delay, const TimerCallback& cb);
  friend void RunEvery(const int64_t interval, const TimerCallback& cb);
};

void RunAt(const TimeStamp& when, const TimerCallback& cb);
void RunAfter(const int64_t delay, const TimerCallback& cb);
void RunEvery(const int64_t interval, const TimerCallback& cb);

#endif
