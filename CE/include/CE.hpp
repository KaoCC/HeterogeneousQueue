
#ifndef _CE_CE_HPP_
#define _CE_CE_HPP_


#ifndef CE_STATIC_LIBRARY
#ifdef WIN32
    #ifdef CE_EXPORT_API
        #define CE_API __declspec(dllexport)
    #else
        #define CE_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #ifdef CE_EXPORT_API
        #define CE_API __attribute__((visibility ("default")))
    #else
        #define CE_API
    #endif
#endif
#else
#define CE_API
#endif




namespace CE {

    class CE_API ComputeEngine {

    public:

        virtual ~ComputeEngine() = 0;


    };


    class CE_API Device {
    public:
        virtual ~Device() = 0;

    };



}



#endif







