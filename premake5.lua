workspace "Luci-Engine"
    architecture "x64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    flags {
        "MultiProcessorCompile"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Luci-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Luci-Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Luci-Engine/vendor/imgui"
IncludeDir["stb"] = "Luci-Engine/vendor/stb"
IncludeDir["glm"] = "Luci-Engine/vendor/glm"

group "Dependencies"
    include "Luci-Engine/vendor/GLFW"
    include "Luci-Engine/vendor/Glad"
    include "Luci-Engine/vendor/imgui"
group ""

project "Luci-Engine"
    location "Luci-Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    pchheader "lucipch.h"
    pchsource "%{prj.name}/src/lucipch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb/**.h",
        "%{prj.name}/vendor/stb/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "LUCI_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "LUCI_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LUCI_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations.Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Luci-Engine/vendor/spdlog/include",
        "Luci-Engine/src",
        "Luci-Engine/vendor",
        "%{IncludeDir.glm}"
    }

    links {
        "Luci-Engine"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "LUCI_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LUCI_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations.Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "on"

project "Sample"
    location "Sample"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Luci-Engine/vendor/spdlog/include",
        "Luci-Engine/src",
        "Luci-Engine/vendor",
        "%{IncludeDir.glm}"
    }

    links {
        "Luci-Engine"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "LUCI_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LUCI_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations.Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "on"
