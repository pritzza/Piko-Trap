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

/* better version (doesnt work):
#include <assert.h>
#include <typeindex>
#include <unordered_map>
#include <vector>


// https://medium.com/@savas/nomad-game-engine-part-7-the-event-system-45a809ccb68f
// ^ this guy is a genius
// This is the interface for MemberFunctionHandler that each specialization will use
class EventBus final
{
private:
    // HandlerFunctionBase and MemberFunctionHandler defined inside EventBus as private members
    // such that they will not exist outside this class
    //
    // This is the interface for MemberFunctionHandler that each specialization will use
    class HandlerFunctionBase
    {
    private:
        // Implemented by MemberFunctionHandler
        virtual void call(Event* e) const = 0;

    public:
        // Call the member function
        void exec(Event* e) const
        {
            call(e);
        }
    };

    template<class GameSystem, class EventType>
    class MemberFunctionHandler : public HandlerFunctionBase
    {
        // A function pointer to a method of type T that returns void and takes in an EventType type ptr
        typedef void (GameSystem::* MemberFunction)(EventType*);

    private:
        GameSystem* instance;   // Pointer to instance with method we want to call
        MemberFunction m;       // Pointer to member function of GameSystem that we want to call

    public:
        MemberFunctionHandler(GameSystem* instance, MemberFunction memberFunction)
            :
            instance{ instance },
            m{ memberFunction }
        {}

        void call(Event* e) const
        {
            // Cast event to the correct type and call member function
            (instance->*m)(static_cast<EventType*>(e));
        }

    };

private:
    std::unordered_map<std::type_index, std::vector<HandlerFunctionBase*>> subscribers;

public:
    ~EventBus()
    {
        for (const auto& it : this->subscribers)
            for (const auto handler : it.second)
                delete handler;
    }

    template<typename EventType>
    void publish(EventType* et) const
    {
        const std::type_index eventID{ typeid(EventType) };

        assert(subscribers.find(eventID) != subscribers.end());

        // go through ever function that is subscribed to the matching
        // eventID and excute the corresponding method
        for (const auto& handler : subscribers.at(eventID))
            if (handler != nullptr)
                handler->exec(et);
    }

    template<class T, class EventType>
    void subscribe(T* instance, void (T::* memberFunction)(EventType*))
    {
        //if constexpr to check T's type?

        const std::type_index eventID{ typeid(EventType) };

        if (subscribers.find(eventID) == subscribers.end())
            subscribers.insert({ eventID, {} });

        subscribers.at(eventID).push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
    }

};
*/