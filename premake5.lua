workspace "Dots"
	architecture "x86_64"
	startproject "CarDot"

	configurations
	{
		"Debug",
		"Release",
		"Distrib"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


group "Dependencies"
include "Eis/vendor/GLFW"
include "Eis/vendor/Glad"
include "Eis/vendor/imgui"
include "Eis/vendor/implot"
group ""

include "Eis"


project "Dots2"
	location "Dots2"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Eis/src",
		"Eis/vendor/spdlog/include",
		"Eis/vendor/imgui",
		"Eis/vendor/implot",
		"Eis/vendor/glm",
		"Eis/vendor/GameNetworkingSockets/include"
	}

	links
	{
		"Eis"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EIS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EIS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distrib"
		defines "EIS_DISTRIB"
		runtime "Release"
		optimize "on"

		project "Dots2"
		location "Dots2" 
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.hpp"
		}

		includedirs
		{
			"%{prj.name}/src",
			"Eis/src",
			"Eis/vendor/spdlog/include",
			"Eis/vendor/imgui",
			"Eis/vendor/implot",
			"Eis/vendor/glm",
			"Eis/vendor/GameNetworkingSockets/include"
		}

		links
		{
			"Eis"
		}

		filter "system:windows"
			systemversion "latest"

		filter "configurations:Debug"
			defines "EIS_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "EIS_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Distrib"
			defines "EIS_DISTRIB"
			runtime "Release"
			optimize "on"


project "CarDot"
	location "CarDot"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Eis/src",
		"Eis/vendor/spdlog/include",
		"Eis/vendor/imgui",
		"Eis/vendor/implot",
		"Eis/vendor/glm",
		"Eis/vendor/GameNetworkingSockets/include"
	}

	links
	{
		"Eis"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EIS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EIS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distrib"
		defines "EIS_DISTRIB"
		runtime "Release"
		optimize "on"

		project "Dots3"
		location "Dots3"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
	
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.hpp"
		}
	
		includedirs
		{
			"%{prj.name}/src",
			"Eis/src",
			"Eis/vendor/spdlog/include",
			"Eis/vendor/imgui",
			"Eis/vendor/implot",
			"Eis/vendor/glm",
			"Eis/vendor/GameNetworkingSockets/include"
		}

		links
		{
			"Eis"
		}

		filter "system:windows"
			systemversion "latest"

		filter "configurations:Debug"
			defines "EIS_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "EIS_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Distrib"
			defines "EIS_DISTRIB"
			runtime "Release"
			optimize "on"