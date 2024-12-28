workspace "Nameless"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nameless/vendor/GLFW/include"
IncludeDir["Glad"] = "Nameless/vendor/Glad/include"
IncludeDir["ImGui"] = "Nameless/vendor/imgui"

include "Nameless/vendor/GLFW"
include "Nameless/vendor/Glad"
include "Nameless/vendor/ImGui"

project "Nameless"
	location "Nameless"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/".. outputdir.. "/%{prj.name}")
	objdir ("bin-int/".. outputdir.. "/%{prj.name}")

	pchheader "nmlspch.h"
	pchsource "Nameless/src/nmlspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"NMLS_PLATFORM_WINDOWS",
			"NMLS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "NMLS_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "NMLS_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "NMLS_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/".. outputdir.. "/%{prj.name}")
	objdir ("bin-int/".. outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Nameless/vendor/spdlog/include",
		"Nameless/src"
	}

	links
	{
		"Nameless"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"NMLS_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "NMLS_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "NMLS_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "NMLS_DIST"
			buildoptions "/MD"
			optimize "On"