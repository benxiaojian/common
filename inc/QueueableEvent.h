/*
 * Event.h
 * Author: Xiao Jian
 */

#pragma once

namespace hj
{

class QueueableEvent
{
public:
    typedef enum event_id {
        kNONE,
        kINFORM,
    }ID;

    QueueableEvent(QueueableEvent::ID id): id(id) {}

    QueueableEvent::ID GetEventId() const
    {
        return id;
    }

private:
    QueueableEvent::ID id;
};

}
