#include "Poller.h"
#include "EPollPoller.h"

#include <stdio.h>

Poller* Poller::newDefaultPoller(EventLoop* loop)
{ //默认不实现poll
    if(::getenv("MUDO_USE_POLL"))
    {
        return nullptr;
    }
    else
    {
        return new EPollPoller(loop);
    }
}