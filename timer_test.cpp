#include <Poco/Util/Timer.h>
#include <Poco/Util/TimerTaskAdapter.h>

#include <memory>
#include <iostream>
#include <queue>
#include <vector>
#include <thread>

class MyTimerTask{
 public:
  MyTimerTask(Poco::Event& event, std::queue<int>& queue, int event_value)
      : event_(event),
        queue_(queue),
        event_value_(event_value)
  {}
  
  void onTimer(Poco::Util::TimerTask& task) {
    std::cout << "OnTimer (EventType: " << event_value_ << ")" << std::endl;
    event_.set();
  }
  
 private:
  Poco::Event& event_;
  std::queue<int>& queue_;
  int event_value_;
};

int main(int argc, char *argv[])
{
  std::queue<int> queue;
  Poco::Util::Timer timer;
  using Duration = Poco::Timestamp::TimeDiff;
  Duration kTimeDiff = 500 * 1000; // 500 msec
  Poco::Event event;
  using Schedule = std::pair<Duration, MyTimerTask>;
  std::vector<Schedule> tasklist = {
    {1000 * 1000, MyTimerTask(event, queue, 10)},
    { 500 * 1000, MyTimerTask(event, queue,  5)},
    { 200 * 1000, MyTimerTask(event, queue,  2)}
  };

  using taskptr = Poco::Util::TimerTask::Ptr;  
  Poco::Timestamp time;
  
  for (auto& schedule: tasklist) {
    taskptr ptask = new Poco::Util::TimerTaskAdapter<MyTimerTask>(schedule.second, &MyTimerTask::onTimer);
    auto expire_at = time + schedule.first;
    timer.schedule(ptask, expire_at);
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  return 0;
}
 
