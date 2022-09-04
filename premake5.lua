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

    include "Amoeba/vendor/GLFW"
    include "Amoeba/vendor/Glad"
    include "Amoeba/vendor/imgui"

    -- startproject "Sandbox" todo: added in repo, but printing error onbuild?


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
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
		defines "AMOEBA_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "AMOEBA_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "AMOEBA_DIST"
		buildoptions "/MD"
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
        symbols "On"

    filter "configurations:Release"
        defines "AMOEBA_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "AMOEBA_DIST"
        buildoptions "/MD"
        optimize "On"
