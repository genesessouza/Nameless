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
IncludeDir["glm"] = "Nameless/vendor/glm"

include "Nameless/vendor/GLFW"
include "Nameless/vendor/Glad"
include "Nameless/vendor/ImGui"

project "Nameless"
	location "Nameless"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/".. outputdir.. "/%{prj.name}")
	objdir ("bin-int/".. outputdir.. "/%{prj.name}")

	pchheader "nmlspch.h"
	pchsource "Nameless/src/nmlspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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

		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"NMLS_PLATFORM_WINDOWS",
			"NMLS_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

		filter "configurations:Debug"
			defines "NMLS_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "NMLS_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "NMLS_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

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
		"Nameless/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Nameless"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"
		buildoptions "/utf-8"

		defines
		{
			"NMLS_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "NMLS_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "NMLS_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "NMLS_DIST"
			optimize "on"