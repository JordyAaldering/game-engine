include "./vendor/premake/premake_customization/solution_items.lua"
include "dependencies.lua"

workspace "Luci-Engine"
	architecture "x86_64"
	startproject "Luci-Editor"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	solution_items {
		".editorconfig"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "Luci-Engine/vendor/GLFW"
	include "Luci-Engine/vendor/Glad"
	include "Luci-Engine/vendor/imgui"
	include "Luci-Engine/vendor/yaml-cpp"
group ""

include "Luci-Engine"
include "Luci-Editor"
include "Sandbox"
