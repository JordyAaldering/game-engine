project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Luci-Engine/vendor/spdlog/include",
		"%{wks.location}/Luci-Engine/src",
		"%{wks.location}/Luci-Engine/vendor",
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
