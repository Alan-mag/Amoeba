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


project "Amoeba"
    location "Amoeba"
    kind "SharedLib"
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
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
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
