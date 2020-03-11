#include <functional>
#include "timewheel.h"

class Timer {
 private:
  TimeWheel timewheel_;

 public:
  Timer();
  void Start();
   
  void RunAfter(int64_t delay, std::function<void(void)>& cb);
  void RunEvery(int64_t interval, std::function<void(void)>& cb);
};
