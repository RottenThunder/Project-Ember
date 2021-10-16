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

	targetdir ("bin/%{cfg.buildcfg}-x64/%{prj.name}")
	objdir ("bin-int/%{cfg.buildcfg}-x64/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EM_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}-x64/Game")
		}

	filter "configurations:Debug"
		defines "EM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EM_DIST"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

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
		"vendor/spdlog/include"
	}

	links
	{
		"Ember"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EM_DIST"
		optimize "On"