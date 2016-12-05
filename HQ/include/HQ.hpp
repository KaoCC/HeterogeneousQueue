
#ifndef _HQ_HQ_HPP_
#define _HQ_HQ_HPP_

#include <functional>

//#define HQ_API_VERSION 1.0

//tmp
#define HQ_STATIC_LIBRARY 1

#ifndef HQ_STATIC_LIBRARY
#ifdef WIN32
    #ifdef EXPORT_API
        #define HQAPI __declspec(dllexport)
    #else
        #define HQAPI __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #ifdef EXPORT_API
        #define HQAPI __attribute__((visibility ("default")))
    #else
        #define HQAPI
    #endif
#endif
#else
#define HQAPI
#endif



namespace HQ {



    class HQAPI Event {

    public:

        virtual void wait() = 0;
        virtual void signal() = 0;
        virtual bool isComplete() const = 0;

        virtual ~Event() = 0;

    };


    class HQAPI TaskParameter {

    public:

            // test only
        virtual ~TaskParameter() = 0;
    };


    class HQAPI Task {
 
    public:
        using RunFunctionType = std::function<void(TaskParameter*)>;

        virtual RunFunctionType getRunFunction() = 0;
        virtual TaskParameter* getTaskParameter() = 0;
        virtual Event* getEvent() = 0;

        // tmp: for testing only !
        virtual ~Task() = 0;    
    };


    HQAPI void hqInit();
    HQAPI void hqDestroy();

    HQAPI void hqEnqueue(Task* task);


//for testing
    HQAPI Event* hqCreateEvent();
    HQAPI void hqDestroyEvent(Event* event);

}


#endif