/*
 * Event.h
 * Author: Xiao Jian
 */
#include <mutex>
#include <queue>
#include <condition_variable>
#include <QueueableEvent.h>
#include <GobalType.h>
#include <Thread.h>

namespace hj
{

class QueueableThread : public Thread
{
    typedef std::shared_ptr<QueueableEvent> QueueableEventPtr;

public:
    QueueableThread(const char *name = "Queue with Thread");
    virtual ~QueueableThread(void);

    s32 Enqueue(std::shared_ptr<QueueableEvent> event);
    virtual std::shared_ptr<QueueableEvent> Dequeue(void);

private:
    std::mutex queue_mutex;
    std::condition_variable queue_condition;
    std::queue<QueueableEventPtr> event_queue;
};

}
