workspace "Ember"
	architecture "x86_64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/glfw/include"
IncludeDir["GLAD"] = "vendor/glad/include"

group "Dependencies"
	include "vendor/glfw"
	include "vendor/glad"
group ""

project "Ember"
	location "Ember"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/%{cfg.buildcfg}-x64-%{cfg.system}/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-x64-%{cfg.system}/%{prj.name}")

	pchheader "empch.h"
	pchsource "Ember/src/empch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"vendor/spdlog/include"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_WINDOWS",
			"EM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/%{cfg.buildcfg}-x64-%{cfg.system}/Game/\"")
		}

	filter "system:linux"
		pic "On"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_LINUX",
			"EM_BUILD_DYNAMIC_LIBRARY",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/%{cfg.buildcfg}-x64-%{cfg.system}/Game/\"")
		}

	filter "configurations:Debug"
		defines "EM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EM_DIST"
		runtime "Release"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/%{cfg.buildcfg}-x64-%{cfg.system}/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-x64-%{cfg.system}/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Ember/src",
		"vendor/spdlog/include"
	}

	links
	{
		"Ember"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		pic "On"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "EM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EM_DIST"
		runtime "Release"
		optimize "On"
