workspace "Luci-Engine"
    architecture "x64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Luci-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Luci-Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Luci-Engine/vendor/imgui"

group "Dependencies"
    include "Luci-Engine/vendor/GLFW"
    include "Luci-Engine/vendor/Glad"
    include "Luci-Engine/vendor/imgui"

group ""

project "Luci-Engine"
    location "Luci-Engine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lucipch.h"
    pchsource "%{prj.name}/src/lucipch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines {
            "LUCI_PLATFORM_WINDOWS",
            "LUCI_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }
    
    filter "configurations:Debug"
        defines "LUCI_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LUCI_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations.Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Luci-Engine/vendor/spdlog/include",
        "Luci-Engine/src"
    }

    links {
        "Luci-Engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "LUCI_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LUCI_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LUCI_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations.Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "On"
