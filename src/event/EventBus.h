#pragma once

#include <iostream>
#include <map>
#include <list>
#include <typeindex>

#ifndef ALL_EVENT_TYPES
#define ALL_EVENT_TYPES
#include "EntityCollisionEvent.h"
#include "GameStateMachineOperationEvent.h"
#endif

// https://medium.com/@savas/nomad-game-engine-part-7-the-event-system-45a809ccb68f
// ^ this guy is a genius
// This is the interface for MemberFunctionHandler that each specialization will use
class HandlerFunctionBase
{
private:
    // Implemented by MemberFunctionHandler
    virtual void call(Event* e) = 0;

public:
    // Call the member function
    void exec(Event* e)
    {
        call(e);
    }

};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
    // function pointer to a method of T that returns void and takes in EventType
    typedef void (T::* MemberFunction)(EventType*);

private:
    // Pointer to class instance
    T* instance;

    // Pointer to member function
    MemberFunction m;

public:
    MemberFunctionHandler(T* instance, MemberFunction memberFunction)
        :
        instance{ instance },
        m{ memberFunction }
    {};

    void call(Event* e)
    {
        // Cast event to the correct type and call member function
        (instance->*m)(static_cast<EventType*>(e));
    }

};

//typedef std::list<HandlerFunctionBase*> HandlerList;
class EventBus
{
    // TODO write deconstructor to free dynamically things
private:
    std::map<std::type_index, std::list<HandlerFunctionBase*>*> subscribers;

public:
    template<typename EventType>
    void publish(EventType* et)
    {
        std::list<HandlerFunctionBase*>* handlers = subscribers[typeid(EventType)];

        if (handlers == nullptr)
            return;

        for (auto& handler : *handlers)
            if (handler != nullptr)
                handler->exec(et);
    }

    template<class T, class EventType>
    void subscribe(T* instance, void (T::* memberFunction)(EventType*))
    {
        std::list<HandlerFunctionBase*>* handlers = subscribers[typeid(EventType)];

        //First time initialization
        if (handlers == nullptr)
        {
            handlers = new std::list<HandlerFunctionBase*>();
            subscribers[typeid(EventType)] = handlers;
        }

        handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

};

/* example:

struct Event{
    int a=2;
};

struct SomeEventB : public Event{
    int b=4;
};

struct SomeEventA : public Event{
    int b=5;
};

struct SomeSystem
{
    void handleSomeEvent(SomeEventA* se)
    {
        std::cout << se->b;
    }

};

int main()
{
    EventBus bus;
    SomeSystem s;
    
    bus.subscribe(&s, &SomeSystem::handleSomeEvent);

    SomeEventA e;
    bus.publish(&e);
}

*/