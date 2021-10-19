workspace "Ember"
	architecture "x86_64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

project "Ember"
	location "Ember"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")

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
		"vendor/GLFW/include",
		"vendor/spdlog/include"
	}

	links
	{
		"vendor/GLFW/lib/glfw3.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"EM_PLATFORM_WINDOWS",
			"EM_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}-x64/Game")
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

	targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Ember/src",
		"vendor/GLFW/include",
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