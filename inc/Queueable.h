/*
 * Queueable.h
 * Author: Xiao Jian
 */
#pragma once

#include <queue>
#include <memory>

#include <GobalType.h>
#include <QueueableEvent.h>

namespace hj
{

class Queueable
{
    typedef std::shared_ptr<QueueableEvent> QueueableEventPtr;
private:
    std::queue<QueueableEventPtr> event_queue;

public:
    virtual ~Queueable() {}

    virtual s32 Enqueue(std::shared_ptr<QueueableEvent> event)
    {
        event_queue.push(event);

        return 0;
    }

    virtual std::shared_ptr<QueueableEvent> Dequeue(void)
    {
        std::shared_ptr<QueueableEvent> event;

        if (!event_queue.empty()) {
            event = event_queue.front();
            event_queue.pop();
        }

        return event;
    }

};

}
