/*
 * test.cpp
 * Author: Xiao Jian
 */
#include <QueueableThread.h>
#include <QueueableEvent.h>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace hj;

//class Test : public Thread
//{
//public:
//    Test(const char *name):Thread(name) {}
//
//    s32 ThreadTask(void)
//    {
//        cout << GetThreadName() << endl;
//
//        return 0;
//    }
//};
//
//
//int main()
//{
//    Test a("123");
//    Test b("234");
//
//    a.StartThread();
//    b.StartThread();
//
//    a.StopThread();
//    b.StopThread();
//}


class Test : public QueueableThread
{
public:
    Test() {}

    s32 ThreadTask(void)
    {
        cout << "start thread" << endl;
        while (ThreadJoinable()) {
            cout << "loop" << endl;
            shared_ptr<QueueableEvent> dequeue_event = Dequeue();
            cout << "dequeue" << endl;
        }

        return 0;
    }
};


int main()
{
    Test t;

    t.StartThread();

    shared_ptr<QueueableEvent> event = make_shared<QueueableEvent>(QueueableEvent::kINFORM);

    t.Enqueue(event);
    t.Enqueue(event);
    while (1) {
        sleep(1000);
    }
}
