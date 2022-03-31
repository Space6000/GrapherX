workspace "GrapherX-Dev"
    startproject "SandBox"
	architecture "x64"
	
	configurations {
	"Debug",
	"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "GrapherX/vendor/imgui"
include "GrapherX/vendor/imgui"

project "GrapherX"

	location "GrapherX"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/Spdlog/include"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"ImGui"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GP_RELEASE"
		runtime "Release"
		optimize "on"


project "SandBox"

	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	links
	{
		"GrapherX"
	}
	
	
	includedirs
	{
		"GrapherX/vendor/spdlog/include",
		"GrapherX/src",
		"GrapherX/vendor"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GP_RELEASE"
		runtime "Release"
		optimize "on"
