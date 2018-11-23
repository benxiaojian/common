/*
 * QueueableThread.cpp
 * Author: Xiao Jian
 */
#include <iostream>
#include <QueueableThread.h>
#include <Thread.h>
using namespace std;


namespace hj
{

QueueableThread::QueueableThread(const char *name) :
    Thread(name)
{

}


QueueableThread::~QueueableThread(void)
{

}


s32 QueueableThread::Enqueue(std::shared_ptr<QueueableEvent> event)
{
    Mutex::LockMutex(queue_mutex);

    event_queue.push(event);

    Mutex::ConditionNotifyOne(queue_condition);
    Mutex::UnlockMutex(queue_mutex);

    return 0;
}


shared_ptr<QueueableEvent> QueueableThread::Dequeue(void)
{
    shared_ptr<QueueableEvent> dequeue_event;

    Mutex::LockMutex(queue_mutex);

    while (event_queue.empty()) {
        if (Mutex::ConditionWaitTimeForSeconds(queue_condition, 10, queue_mutex)) {
            std::cout << "timeout" << std::endl;
            return dequeue_event;
        }
    }

    dequeue_event = event_queue.front();
    event_queue.pop();

    Mutex::UnlockMutex(queue_mutex);

    return dequeue_event;
}


}
