#pragma once
#include "noncopyable.h"
#include <functional>
#include <string>
#include <vector>
#include <memory>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool:noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThreadPool(EventLoop* baseloop,const std::string& nameArg);
    ~EventLoopThreadPool();
    void setThreadNum(int numThreads){numThreads_ = numThreads;}
    void start(const ThreadInitCallback& cb = ThreadInitCallback());
    
    //baseLoop_以轮询的方式分配channel给subloop
    EventLoop* getNextLoop();
    std::vector<EventLoop*> getAllLoops();
    bool started() const {return started_;}
    const std::string name() const {return name_;}
private:
    EventLoop* baseLoop_;
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;//记录轮询索引
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};