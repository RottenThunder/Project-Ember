project "ImGui"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir ("../../../bin/%{cfg.buildcfg}-x64-%{cfg.system}/%{prj.name}")
	objdir ("../../../bin-int/%{cfg.buildcfg}-x64-%{cfg.system}/%{prj.name}")

	files
	{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_tables.cpp",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp"
	}

    defines
	{
		"IMGUI_API=__declspec(dllexport)"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
