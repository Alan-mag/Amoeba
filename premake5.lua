workspace "Amoeba"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    -- Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["GLFW"] = "Amoeba/vendor/GLFW/include"

    include "Amoeba/vendor/GLFW"


project "Amoeba"
    location "Amoeba"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "amoebapch.h"
    pchsource "Amoeba/src/amoebapch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links 
	{ 
		"GLFW",
		"opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "AMOEBA_PLATFORM_WINDOWS",
            "AMOEBA_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "AMOEBA_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AMOEBA_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "AMOEBA_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Amoeba/vendor/spdlog/include",
        "Amoeba/src"
    }

    links
    {
        "Amoeba"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "AMOEBA_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "AMOEBA_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AMOEBA_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "AMOEBA_DIST"
        optimize "On"
