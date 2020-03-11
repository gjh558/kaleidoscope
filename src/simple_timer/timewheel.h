
#include <vector>
#include <list>
#include <functional>
#include <memory>
#include <atomic>
#include <sys/time.h>

class TimeWheel {
 public:
  struct Timer {
	  std::function<void(void)> callback_;
    struct timeval when_;
    int64_t interval_;
    bool periodic_;
  };

  std::vector<std::list<std::shared_ptr<Timer>>> time_wheel_;
  std::atomic<int> cur_index_;
  int size_;
  int tick_;

  TimeWheel(int period, int tick);
  ~TimeWheel() {
    for (auto &l : time_wheel_)
      l.clear();
  }
  	  
  void AddTimer(struct timeval &when, int64_t interval, bool periodic, std::function<void(void)>& cb);
  void Tick();
};



