

workspace "HeterogeneousQueue"

    location "Generated"

    language "C++"

    configurations {"Debug", "Release"}
    platforms {"x64", "x32"}

    filter { "platforms:x64" }
        architecture "x86_64"
    filter { "platforms:x32" }
        architecture "x86"
    
    filter { }


    filter { "configurations:Debug" }
        flags { "Symbols" }

    filter { "configurations:Release" }
        -- Release should be optimized
        optimize "On"

    -- Reset the filter for other settings
    filter { }


    targetdir ("Build/Bin/%{prj.name}/%{cfg.buildcfg}/%{cfg.platform}")
    objdir ("Build/Obj/%{prj.name}/%{cfg.buildcfg}/%{cfg.platfrom}")


    dofile ("./OpenCLSearch.lua" )


    -- linkage def
    defines {"HQ_STATIC_LIBRARY"}
    defines {"CE_STATIC_LIBRARY"}



    -- CLAL (OpenCL Abstraction Layer)

    project "CLAL"

        kind "StaticLib"
        --defines {CLAL_STATIC_LIBRARY}

        
        files {"CLAL/**.cpp", "CLAL/**.hpp"}



    -- Compute Engine    

    project "CE"

        kind "StaticLib"
        --defines {"CE_STATIC_LIBRARY"}

        includedirs "CE/include"
        files  {"CE/**.cpp", "CE/**.hpp"}


    -- The HQ

    project "HQ"

        kind "StaticLib"
        --defines {"HQ_STATIC_LIBRARY"}

        -- tmp: linkage
        links "CE"
        includedirs {"HQ/include", "CE/include"}

        files {"HQ/**.cpp", "HQ/**.hpp"}


    -- Test Drive
    project "Test"
        kind "ConsoleApp"

        links "HQ"

        includedirs {"HQ/include", "CE/include"}
        files {"Test/**.cpp"}




