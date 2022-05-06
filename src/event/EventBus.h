#pragma once

#include <map>
#include <typeindex>
#include <vector>

#ifndef ALL_EVENT_TYPES
#define ALL_EVENT_TYPES
#include "EntityCollisionEvent.h"
#include "GameStateMachineOperationEvent.h"
#endif

// Source:
// https://medium.com/@savas/nomad-game-engine-part-7-the-event-system-45a809ccb68f
// ^ this guy is a genius
class EventBus
{
private:
    //// Class definitions for HandlerFunctionBase and MemberFunctionHandler are put inside
    //// of the EventBus class and declared private members so nowhere outside of EventBus
    //// can they be created or accessed.
 
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
        // A function pointer to a method of type T that returns void and takes in an EventType type ptr
        typedef void (T::* MemberFunction)(EventType*);

    private:
        T* instance;        // Pointer to instance with method we want to call
        MemberFunction m;   // Pointer to member function of GameSystem that we want to call

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

// EventBus body start:
private:
    std::map<std::type_index, std::vector<HandlerFunctionBase*>> subscribers;

public:
    template<typename EventType>
    void publish(EventType* et)
    {
        const std::type_index eventID{ typeid(EventType) };

        // if we have handlers for a type of event
        if (subscribers.find(eventID) != subscribers.end())
        {
            // get the vector containing all the handlers for that event
            auto& handlers{ subscribers.at(eventID) };

            // and execute them
            for (auto& funcHandler : handlers)
                funcHandler->exec(et);
        }
    }

    template<class T, class EventType>
    void subscribe(T* instance, void (T::* memberFunction)(EventType*))
    {
        const std::type_index eventID{ typeid(EventType) };

        // if no handlers exist for an event, create a new vector for the handlers of that event
        if (subscribers.find(eventID) == subscribers.end())
            subscribers.insert({ eventID, std::vector<HandlerFunctionBase*>() });

        auto funcHandler{ new MemberFunctionHandler<T, EventType>(instance, memberFunction) };

        subscribers.at(eventID).push_back(funcHandler);
    }

};

/* usage example:

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