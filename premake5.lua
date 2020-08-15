workspace "Luci-Engine"
    architecture "x86_64"
    startproject "Luci-Editor"

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
IncludeDir["spdlog"] = "Luci-Engine/vendor/spdlog/include"
IncludeDir["GLFW"]   = "Luci-Engine/vendor/GLFW/include"
IncludeDir["Glad"]   = "Luci-Engine/vendor/Glad/include"
IncludeDir["ImGui"]  = "Luci-Engine/vendor/imgui"
IncludeDir["stb"]    = "Luci-Engine/vendor/stb"
IncludeDir["glm"]    = "Luci-Engine/vendor/glm"
IncludeDir["entt"]   = "Luci-Engine/vendor/entt/include"

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
        IncludeDir["stb"] .. "/**.h",
        IncludeDir["stb"] .. "/**.cpp",
        IncludeDir["glm"] .. "/**.hpp",
        IncludeDir["glm"] .. "/**.inl"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
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

    filter "configurations:Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "on"

project "Luci-Editor"
    location "Luci-Editor"
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
        "Luci-Engine/src",
        "Luci-Engine/vendor",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
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

    filter "configurations:Dist"
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
        "Luci-Engine/src",
        "Luci-Engine/vendor",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
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

    filter "configurations:Dist"
        defines "LUCI_DIST"
        runtime "Release"
        optimize "on"
