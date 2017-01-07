
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

#include "Executable.hpp"
#include "Function.hpp"

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
        //using RunFunctionType = std::function<void(TaskParameter*)>;

        virtual CE::Function const* getRunFunction(size_t index) = 0;
        virtual TaskParameter* getTaskParameter() = 0;


		virtual size_t getGlobalSize() = 0;

        virtual Event* getEvent() = 0;

        // tmp: for testing only !
        virtual ~Task() = 0;    
    };


    HQAPI void CreateHeterogeneousQueue();
    HQAPI void DestroyHeterogeneousQueue();

    HQAPI void EnqueueHeterogeneousQueue(Task* task);

	HQAPI size_t GetNumberOfUnits();

	//HQAPI CE::Function const* CreateSequentialFunctionWithIndex(size_t index, const char* name, std::function<void(int)>&& f);
	HQAPI CE::Executable* CreateSequentialExecutableWithIndex(size_t index);
	HQAPI CE::Executable* CompileExecutableWithIndex(size_t index, const char* filename, const char* options);

	// KAOCC: Need to delete the Executable !!!

	HQAPI CE::Buffer* CreateBufferWithIndex(size_t index, size_t size);

	// KAOCC: Need to delete Buffers


	// Buffer Read /Write ?

	HQAPI void WriteBufferWithIndex(size_t index, CE::Buffer const* buffer, size_t offset, size_t size, void* src);
	HQAPI void ReadBufferWithIndex(size_t index, CE::Buffer const* buffer, size_t offset, size_t size, void* dst);



	//KAOCC: for testing
	// the Event system needs to be redesigned
    HQAPI Event* CreateEvent();
    HQAPI void DestroyEvent(Event* event);

}


#endif


