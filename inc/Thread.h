/*
 * Thread.h
 * Author: Xiao Jian
 */
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <memory>

#include <GobalType.h>

namespace hj
{

class Mutex
{
public:
    static void LockMutex(std::mutex &thread_mutex);
    static void UnlockMutex(std::mutex &thread_mutex);

    static void ConditionWait(std::condition_variable &condition, std::mutex &thread_mutex);
    static bool ConditionWaitTimeForSeconds(std::condition_variable &condition, s32 timeout, std::mutex &thread_mutex);
    static bool ConditionWaitTimeForMillseconds(std::condition_variable &condition, s32 timeout, std::mutex &thread_mutex);
    static void ConditionNotifyOne(std::condition_variable &condition);
    static void ConditionNotifyAll(std::condition_variable &condition);
};


class Thread
{
public:
    Thread(const char *name = "ThreadWithoutName");
    virtual ~Thread() {}

    virtual s32 StartThread(void);
    virtual s32 StopThread(void);

    bool ThreadJoinable(void);

    virtual s32 ThreadTask(void) = 0;

    std::string &GetThreadName(void);

private:
    std::shared_ptr<std::thread> m_thread;
    std::string m_thread_name;
};

}

