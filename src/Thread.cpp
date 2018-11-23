/*
 * Thread.h
 * Author: Xiao Jian
 */
#include <Thread.h>
#include <chrono>
using namespace std;

namespace hj
{

void *threadFunction(void *args)
{
    Thread *t = (Thread *)args;
    t->ThreadTask();

    return NULL;
}


void Mutex::LockMutex(mutex &thread_mutex)
{
    thread_mutex.lock();
}


void Mutex::UnlockMutex(mutex &thread_mutex)
{
    thread_mutex.unlock();
}


void Mutex::ConditionWait(condition_variable &condition, mutex &thread_mutex)
{
    unique_lock<mutex> lck(thread_mutex);
    condition.wait(lck);
}


bool Mutex::ConditionWaitTimeForSeconds(condition_variable &condition, s32 timeout, mutex &thread_mutex)
{
    unique_lock<mutex> lck(thread_mutex);
    if (condition.wait_for(lck, chrono::seconds{timeout}) == cv_status::timeout) {
        return true;
    }

    return false;
}


bool Mutex::ConditionWaitTimeForMillseconds(condition_variable &condition, s32 timeout, mutex &thread_mutex)
{
    unique_lock<mutex> lck(thread_mutex);
    if (condition.wait_for(lck, chrono::milliseconds{timeout}) == cv_status::timeout) {
        return true;
    }

    return false;
}


void Mutex::ConditionNotifyOne(condition_variable &condition)
{
    condition.notify_one();
}


void Mutex::ConditionNotifyAll(condition_variable &condition)
{
    condition.notify_all();
}



Thread::Thread(const char *name) :
    m_thread_name(name)
{

}


s32 Thread::StartThread(void)
{
    if (ThreadJoinable()) {
        return -1;
    }

    m_thread.reset(new thread(threadFunction, (void *)this));

    return 0;
}


s32 Thread::StopThread(void)
{
    if (!m_thread) {
        return -1;
    }

    m_thread->join();

    return 0;
}


bool Thread::ThreadJoinable(void)
{
    if (m_thread) {
        return m_thread->joinable();
    }

    return false;
}


string &Thread::GetThreadName(void)
{
    return m_thread_name;
}


}


