-- premake5.lua

workspace "AStarSearch"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "AStarSearch"
        location "src"
        kind "ConsoleApp"
        language "C++"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
        
        files
        {
            "src/**.h",
            "src/**.cpp"
        }
        
        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"
            
            defines
            {
                "PLATFORM_WINDOWS",
            }
            
        filter "configurations:Debug"
            defines "ENGINE_DEBUG"
            symbols "On"
            
        filter "configurations:Release"
            defines "ENGINE_RELEASE"
            optimize "On"
            
        filter "configurations:Dist"
            defines "ENGINE_DIST"
            optimize "On"