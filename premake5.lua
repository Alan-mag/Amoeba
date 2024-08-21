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
    IncludeDir["Glad"] = "Amoeba/vendor/Glad/include"
    IncludeDir["ImGui"] = "Amoeba/vendor/imgui"
    IncludeDir["glm"] = "Amoeba/vendor/glm"
    IncludeDir["stb_image"] = "Amoeba/vendor/stb_image"

    group "Dependencies"
        include "Amoeba/vendor/GLFW"
        include "Amoeba/vendor/Glad"
        include "Amoeba/vendor/imgui"

    -- startproject "Sandbox" todo: added in repo, but printing error onbuild?


project "Amoeba"
    location "Amoeba"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "amoebapch.h"
    pchsource "Amoeba/src/amoebapch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
        "Glad",
        "ImGui",
		"opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "AMOEBA_PLATFORM_WINDOWS",
            "AMOEBA_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
		defines "AMOEBA_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "AMOEBA_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "AMOEBA_DIST"
		buildoptions "/MD"
		optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"

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
        "Amoeba/src",
        "Amoeba/vendor",
        "%{IncludeDir.glm}"
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
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "AMOEBA_RELEASE"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "AMOEBA_DIST"
        buildoptions "/MD"
        optimize "on"
