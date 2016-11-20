

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

    -- The Ray Tracer

    project "HQ"

        kind "ConsoleApp"
        includedirs "HQ/include"

        files {"HQ/src/**.cpp", "HQ/kernel/**.cl"}








